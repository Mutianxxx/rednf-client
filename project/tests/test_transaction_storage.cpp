#include "dnf/storage.hpp"
#include <chrono>
#include <iomanip>
#include <sstream>
#include <stdexcept>
#ifdef _WIN32
#include <windows.h>
#else
#include <sys/wait.h>
#include <unistd.h>
#endif

namespace dnf {
namespace {
namespace fs = std::filesystem;
Json character(const std::string &name = "Storage test") {
    return {{"name", name}, {"class", "swordman"}, {"skills", {{"64", 0}}},
        {"identity", {{"job_id", 0}, {"growtype", 0}, {"awakening", 0}, {"future_identity", 17}}},
        {"future_character", Json::array({1, 3, 5})}};
}
Json root(int schema = 4) {
    Json out = {{"schema", schema}, {"characters", std::vector<Json>(20, nullptr)},
                {"future_root", {{"ordered", Json::array({"a", "b", "a"})}}}};
    out["characters"][0] = character();
    return out;
}
void stageGeneration(CharacterStore &store, int generation) {
    auto &c = store.data["characters"][0];
    c["progression"] = {{"gold", generation * 100}, {"ledger", {{"kill-A", generation}}}};
    c["region_session"] = {{"world", {{"monster_hp", generation == 1 ? 100 : 0}}},
        {"rooms", Json::array({generation})}, {"drops", {{"claimed", generation == 2}}}};
    c["simulation"] = {{"tick", generation * 60}, {"rng", {{"loot", generation * 123}}},
        {"pending_events", Json::array({{{"id", generation}, {"kind", "reward"}}})}};
}
Json sealedFixture(Json value) {
    value["_storage"].erase("checksum");
    // Independent standard CRC32 fixture generation lets the following tests
    // exercise semantic envelope validation rather than only bad checksums.
    uint32_t crc = 0xffffffffu;
    for (const unsigned char byte : value.dump()) {
        crc ^= byte;
        for (int bit = 0; bit < 8; ++bit) crc = (crc >> 1) ^ (0xedb88320u & (0u - (crc & 1u)));
    }
    std::ostringstream out;
    out << std::hex << std::setfill('0') << std::setw(8) << (crc ^ 0xffffffffu);
    value["_storage"]["checksum"] = out.str();
    return value;
}
Json formatOneFixture(const std::string &content) {
    auto value = root(5);
    value["characters"][0]["uuid"] = "10000000-0000-4000-8000-000000000001";
    const std::string first = "20000000-0000-4000-8000-000000000001", second = "20000000-0000-4000-8000-000000000002";
    Json receipts = {{"purchase-old", {{"request_id", "purchase-old"}, {"commit_id", first},
        {"generation", uint64_t(1)}, {"content_identity", content}, {"future_receipt", {{"preserve", true}}}}},
        {"save:deliberate-business-request", {{"request_id", "save:deliberate-business-request"}, {"commit_id", second},
        {"generation", uint64_t(2)}, {"content_identity", content}, {"future_receipt", Json::array({2, 1, 2})}}}};
    value["_storage"] = {{"format", 1}, {"generation", uint64_t(2)}, {"commit_id", second}, {"parent_commit", first},
        {"request_id", "save:deliberate-business-request"}, {"content_identity", content},
        {"checksum_kind", "crc32-json-utf8-v1"}, {"receipts", receipts}, {"future_envelope", {{"preserve", 19}}},
        {"kind", "old-uninterpreted-kind"}, {"result", {{"old_uninterpreted_result", true}}}};
    return sealedFixture(std::move(value));
}
// This child opens the same OS handle/lock protocol in another process. The
// constructor test separately verifies CharacterStore uses that protocol.
bool externalWriterBlocked(const fs::path &directory) {
#ifdef _WIN32
    std::wstring lock = (directory / ".characters.writer.lock").wstring();
    size_t at = 0;
    while ((at = lock.find(L'\'', at)) != std::wstring::npos) { lock.insert(at, 1, L'\''); at += 2; }
    wchar_t system[MAX_PATH]{};
    if (!GetSystemDirectoryW(system, MAX_PATH)) throw std::runtime_error("Cannot find system PowerShell for lock probe");
    const auto powershell = fs::path(system) / "WindowsPowerShell/v1.0/powershell.exe";
    std::wstring command = L"\"" + powershell.wstring() + L"\" -NoLogo -NoProfile -NonInteractive -Command \"try { $f = [IO.File]::Open('" +
        lock + L"', [IO.FileMode]::OpenOrCreate, [IO.FileAccess]::ReadWrite, [IO.FileShare]::Read); $f.Dispose(); exit 0 } catch { exit 23 }\"";
    STARTUPINFOW startup{}; startup.cb = sizeof(startup);
    PROCESS_INFORMATION process{};
    if (!CreateProcessW(powershell.c_str(), command.data(), nullptr, nullptr, FALSE, CREATE_NO_WINDOW,
                        nullptr, nullptr, &startup, &process))
        throw std::runtime_error("Cannot start cross-process save lock probe");
    CloseHandle(process.hThread);
    if (WaitForSingleObject(process.hProcess, 15000) != WAIT_OBJECT_0) {
        TerminateProcess(process.hProcess, 24); CloseHandle(process.hProcess);
        throw std::runtime_error("Cross-process save lock probe timed out");
    }
    DWORD result = 0; GetExitCodeProcess(process.hProcess, &result); CloseHandle(process.hProcess);
    if (result != 0 && result != 23) throw std::runtime_error("Unexpected lock probe exit code");
    return result == 23;
#else
    const auto child = ::fork();
    if (child < 0) throw std::runtime_error("Cannot fork save lock probe");
    if (child == 0) {
        try { CharacterStore competing(directory); ::_exit(0); } catch (...) { ::_exit(23); }
    }
    int result = 0;
    if (::waitpid(child, &result, 0) != child || !WIFEXITED(result)) throw std::runtime_error("Save lock probe failed");
    return WEXITSTATUS(result) == 23;
#endif
}
}

Json runTransactionStorageTests() {
    Json checks = Json::array();
    auto check = [&](bool condition, const std::string &message) {
        if (!condition) throw std::runtime_error("Transactional save: " + message);
        checks.push_back(message);
    };
    auto rejects = [](const std::function<void()> &operation) {
        try { operation(); } catch (const std::exception &) { return true; }
        return false;
    };
    const auto stamp = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    const auto directory = fs::absolute(fs::path("cache/transaction-storage-tests") / std::to_string(stamp));
    fs::create_directories(directory);
    const std::string content = "test-content-A";
    for (int schema = 1; schema <= 4; ++schema) {
        const auto path = directory / ("migration-" + std::to_string(schema));
        atomicJson(path / "characters.json", root(schema));
        const auto original = readFile(path / "characters.json");
        check(rejects([&] { CharacterStore denied(path, content); }), "Schema " + std::to_string(schema) + " cannot bind to content without explicit import");
        check(readFile(path / "characters.json") == original, "Refused legacy import leaves source bytes intact: " + std::to_string(schema));
        CharacterStore imported(path, content, true);
        imported.commit("import");
        const auto firstUuid = imported.data["characters"][0]["uuid"];
        imported.close();
        CharacterStore restored(path, content);
        check(restored.data["schema"] == 5 && restored.data["characters"][0]["uuid"] == firstUuid &&
            restored.data["characters"][0]["skills"]["64"] == 0, "Schema " + std::to_string(schema) + " migrates to stable UUIDs and preserves explicit skill zero");
        check(restored.data["future_root"] == root(schema)["future_root"] &&
            restored.data["characters"][0]["future_character"] == Json::array({1, 3, 5}) &&
            restored.data["characters"][0]["identity"]["future_identity"] == 17,
            "Migration preserves unknown root, character and identity fields: " + std::to_string(schema));
        bool archived = false;
        for (const auto &file : fs::directory_iterator(path))
            if (file.path().filename().u8string().find("characters.legacy.") == 0)
                archived = archived || readFile(file.path()) == original;
        check(archived && readFile(path / "characters.bak.json") == original, "Legacy original is archived and retained as last-good backup: " + std::to_string(schema));
    }
    {
        const auto path = directory / "writer";
        CharacterStore first(path);
        check(rejects([&] { CharacterStore competing(path); }), "A second CharacterStore cannot write to the same directory");
        check(externalWriterBlocked(path), "Independent process cannot acquire the save directory write handle");
        first.close();
        check(rejects([&] { first.save(); }), "Explicitly closed stores cannot resume writing");
        check(!externalWriterBlocked(path), "OS write lock releases after explicit close");
        CharacterStore reopened(path);
        reopened.data = root(); reopened.commit("initial");
        const auto uuid = reopened.data["characters"][0]["uuid"];
        reopened.data["characters"][0] = nullptr; reopened.commit("delete-slot");
        reopened.data["characters"][0] = character("Replacement"); reopened.commit("reuse-slot");
        check(reopened.data["characters"][0]["uuid"] != uuid, "Reusing a deleted slot allocates a new character UUID");
        for (int i = 1; i < 20; ++i) reopened.data["characters"][i] = character(std::to_string(i));
        reopened.commit("full-account");
        check(reopened.data["characters"].size() == 20, "All 20 account slots remain compatible");
        reopened.data["characters"].push_back(character("Overflow"));
        const auto previous = readFile(path / "characters.json");
        check(rejects([&] { reopened.commit("overflow"); }) && readFile(path / "characters.json") == previous,
            "An overflowing account is rejected before changing disk state");
    }
    {
        const auto path = directory / "idempotency";
        CharacterStore store(path, content);
        store.data = root(); stageGeneration(store, 1);
        const auto receipt = store.commit("purchase-123");
        const auto bytes = readFile(path / "characters.json");
        check(store.receipt("purchase-123") == receipt && store.receipt("missing").is_null(), "Request receipt lookup identifies completed commands before execution");
        stageGeneration(store, 2);
        check(store.commit("purchase-123") == receipt && store.generation() == 1 && readFile(path / "characters.json") == bytes,
            "Repeating an already committed request does not commit another reward or generation");
        store.commit("next-command"); store.close();
        CharacterStore recovered(path, content);
        check(recovered.receipt("purchase-123") == receipt && recovered.generation() == 2, "Command receipts survive process restart in the same snapshot");
        recovered.close();
        const auto primary = readFile(path / "characters.json"), backup = readFile(path / "characters.bak.json");
        check(rejects([&] { CharacterStore mismatch(path, "test-content-B", true); }) &&
            readFile(path / "characters.json") == primary && readFile(path / "characters.bak.json") == backup,
            "Cross-content mismatch refuses even explicit legacy import and preserves both snapshots");
        auto future = Json::parse(primary); future["schema"] = 6; atomicJson(path / "characters.json", future);
        const auto futureBytes = readFile(path / "characters.json");
        check(rejects([&] { CharacterStore newer(path, content); }) && readFile(path / "characters.json") == futureBytes,
            "Newer primary schema refuses downgrade through an older valid backup");
    }
    {
        const auto path = directory / "checkpoint-separation";
        CharacterStore store(path, content);
        store.data = root(); stageGeneration(store, 1);
        const auto first = store.commit("business-A");
        auto previous = first["commit_id"];
        Json latest;
        for (int n = 2; n <= 33; ++n) {
            stageGeneration(store, n);
            if (n % 2) { store.save(); latest = store.data["_storage"]["result"]; }
            else latest = store.checkpoint();
            const auto &metadata = store.data["_storage"];
            check(store.generation() == uint64_t(n) && metadata["parent_commit"] == previous && metadata["commit_id"] != previous &&
                metadata["format"] == 2 && metadata["kind"] == "checkpoint" && metadata["request_id"].is_null() &&
                metadata["result"] == latest && latest["kind"] == "checkpoint" && latest["request_id"].is_null() &&
                metadata["receipts"].size() == 1 && store.receipt("business-A") == first &&
                store.data["characters"][0]["progression"]["gold"] == n * 100 &&
                store.data["characters"][0]["simulation"]["rng"]["loot"] == n * 123 &&
                store.data["characters"][0]["simulation"]["pending_events"][0]["id"] == n,
                "Checkpoint advances the complete generation and parent chain without growing business receipts: " + std::to_string(n));
            previous = metadata["commit_id"];
        }
        const auto second = store.commit("business-B");
        const auto state = store.data;
        const auto bytes = readFile(path / "characters.json");
        check(second["generation"] == 34 && second["kind"] == "business" &&
            store.data["_storage"]["receipts"].size() == 2 && store.commit("business-A") == first &&
            store.data == state && readFile(path / "characters.json") == bytes,
            "Business receipts remain idempotent across intervening checkpoints and later business commits");
        store.close();
        CharacterStore recovered(path, content);
        check(recovered.generation() == 34 && recovered.receipt("business-A") == first &&
            recovered.commit("business-B") == second && recovered.data == state,
            "Both stable business receipts and the latest checkpoint state survive restart");
    }
    {
        const auto path = directory / "checkpoint-without-receipts";
        CharacterStore store(path, content);
        store.data = root(); store.save();
        check(store.generation() == 1 && store.data["_storage"]["receipts"].empty() &&
            store.data["_storage"]["result"]["generation"] == 1,
            "An initial ordinary save creates a checkpoint without a synthetic UUID receipt");
        store.close();
        CharacterStore recovered(path, content);
        check(recovered.generation() == 1 && recovered.data["_storage"]["receipts"].empty(),
            "A checkpoint with no historical business receipts is a valid recoverable snapshot");
    }
    for (const bool bindLegacy : {false, true}) {
        const auto path = directory / (bindLegacy ? "format1-binding" : "format1-migration");
        const auto original = formatOneFixture(bindLegacy ? "" : content);
        atomicJson(path / "characters.json", original);
        const auto bytes = readFile(path / "characters.json");
        CharacterStore store(path, content, bindLegacy);
        auto expectedReceipts = original["_storage"]["receipts"];
        if (bindLegacy) for (auto &receipt : expectedReceipts) {
            receipt["legacy_content_identity"] = ""; receipt["content_identity"] = content;
        }
        const auto result = store.checkpoint();
        const auto &metadata = store.data["_storage"];
        check(result["generation"] == 3 && metadata["format"] == 2 && metadata["kind"] == "checkpoint" &&
            metadata["receipts"] == expectedReceipts && metadata["future_envelope"] == original["_storage"]["future_envelope"] &&
            store.data["future_root"] == original["future_root"] &&
            store.data["migration_history"].back()["preserved_metadata"]["kind"] == original["_storage"]["kind"] &&
            store.data["migration_history"].back()["preserved_metadata"]["result"] == original["_storage"]["result"],
            "Format 1 upgrades without pruning historical receipts or overwriting unknown metadata: " + std::to_string(bindLegacy));
        bool archived = false;
        for (const auto &file : fs::directory_iterator(path))
            if (file.path().filename().u8string().find("characters.legacy.") == 0)
                archived = archived || readFile(file.path()) == bytes;
        check(archived && readFile(path / "characters.bak.json") == bytes,
            "Format 1 original bytes remain archived and backed up: " + std::to_string(bindLegacy));
        const auto generation = store.generation();
        check(store.commit("save:deliberate-business-request") == expectedReceipts["save:deliberate-business-request"] &&
            store.generation() == generation, "Historical save-prefixed business IDs keep their idempotency guarantee: " + std::to_string(bindLegacy));
        store.save();
        check(store.data["migration_history"].size() == 1 && store.data["_storage"]["receipts"] == expectedReceipts,
            "Later checkpoints neither repeat envelope migration nor grow its receipt table: " + std::to_string(bindLegacy));
        store.close();
        CharacterStore recovered(path, content);
        check(recovered.receipt("purchase-old") == expectedReceipts["purchase-old"] &&
            recovered.receipt("save:deliberate-business-request") == expectedReceipts["save:deliberate-business-request"],
            "Migrated historical receipts retain unknown fields across restart: " + std::to_string(bindLegacy));
    }
    {
        const auto path = directory / "format2-validation";
        CharacterStore store(path / "control", content);
        store.data = root(); store.checkpoint();
        const auto checkpoint = store.data;
        store.commit("control-business");
        const auto business = store.data;
        std::vector<std::pair<std::string, Json>> invalid;
        const auto malformed = [&](const std::string &name, bool useBusiness, const std::function<void(Json &)> &change) {
            auto value = useBusiness ? business : checkpoint; change(value); invalid.emplace_back(name, sealedFixture(std::move(value)));
        };
        malformed("unknown-kind", false, [](Json &value) { value["_storage"]["kind"] = "future-command"; });
        malformed("checkpoint-request", false, [](Json &value) {
            value["_storage"]["request_id"] = "synthetic-checkpoint";
            value["_storage"]["result"]["request_id"] = "synthetic-checkpoint";
        });
        malformed("result-kind", false, [](Json &value) { value["_storage"]["result"]["kind"] = "business"; });
        malformed("result-request", false, [](Json &value) { value["_storage"]["result"]["request_id"] = "not-null"; });
        malformed("result-commit", false, [](Json &value) { value["_storage"]["result"]["commit_id"] = "30000000-0000-4000-8000-000000000001"; });
        malformed("result-generation", false, [](Json &value) { value["_storage"]["result"]["generation"] = uint64_t(7); });
        malformed("result-content", false, [](Json &value) { value["_storage"]["result"]["content_identity"] = "other-content"; });
        malformed("missing-result", false, [](Json &value) { value["_storage"].erase("result"); });
        malformed("missing-business-receipt", true, [](Json &value) { value["_storage"]["receipts"].erase("control-business"); });
        malformed("business-result-mismatch", true, [](Json &value) { value["_storage"]["result"]["future_result"] = 17; });
        malformed("business-request-null", true, [](Json &value) { value["_storage"]["request_id"] = nullptr; value["_storage"]["result"]["request_id"] = nullptr; });
        auto corrupt = checkpoint; corrupt["future_root"]["tampered"] = true;
        invalid.emplace_back("checksum", std::move(corrupt));
        for (const auto &[name, value] : invalid) {
            const auto target = path / name;
            atomicJson(target / "characters.json", value);
            const auto original = readFile(target / "characters.json");
            check(rejects([&] { CharacterStore denied(target, content); }) && readFile(target / "characters.json") == original,
                "Invalid format 2 envelope is rejected without rewriting its bytes: " + name);
        }
        for (const bool futureKind : {false, true}) {
            const auto target = path / (futureKind ? "unknown-kind-backup" : "future-format-backup");
            auto newer = checkpoint;
            if (futureKind) newer["_storage"]["kind"] = "future-command";
            else newer["_storage"]["format"] = 3;
            newer = sealedFixture(std::move(newer));
            atomicJson(target / "characters.json", newer);
            atomicJson(target / "characters.bak.json", checkpoint);
            const auto original = readFile(target / "characters.json");
            check(rejects([&] { CharacterStore denied(target, content); }) && readFile(target / "characters.json") == original,
                "Unsupported envelope semantics refuse downgrade through a valid older backup: " + std::to_string(futureKind));
        }
        store.checkpoint();
        auto extended = store.data;
        extended["_storage"]["future_envelope"] = {{"preserve", Json::array({3, 3, 1})}};
        extended["_storage"]["receipts"]["control-business"]["future_receipt"] = {{"preserve", true}};
        const auto target = path / "future-fields";
        atomicJson(target / "characters.json", sealedFixture(extended));
        CharacterStore future(target, content);
        future.checkpoint();
        check(future.data["_storage"]["future_envelope"] == extended["_storage"]["future_envelope"] &&
            future.receipt("control-business") == extended["_storage"]["receipts"]["control-business"],
            "Format 2 checkpoints preserve unknown envelope and historical receipt fields");
    }
    const std::array<SaveFailurePoint, 7> boundaries = {SaveFailurePoint::BeforeWrite, SaveFailurePoint::AfterWrite,
        SaveFailurePoint::AfterFlush, SaveFailurePoint::AfterValidation, SaveFailurePoint::AfterBackup,
        SaveFailurePoint::BeforePublish, SaveFailurePoint::AfterPublish};
    for (size_t index = 0; index < boundaries.size(); ++index) {
        const auto path = directory / ("failure-" + std::to_string(index));
        CharacterStore store(path, content);
        store.data = root(); stageGeneration(store, 1); store.commit("generation-1");
        stageGeneration(store, 2);
        store.setFailureInjector([&](SaveFailurePoint point) { if (point == boundaries[index]) throw std::runtime_error("Injected disk boundary failure"); });
        check(rejects([&] { store.commit("generation-2"); }) && store.hasPendingCommit(), "Disk boundary failure retains an immutable candidate: " + std::to_string(index));
        const auto disk = Json::parse(readFile(path / "characters.json"));
        check(disk["_storage"]["generation"] == (boundaries[index] == SaveFailurePoint::AfterPublish ? 2 : 1),
            "Failure exposes either the entire previous generation or the entire new generation: " + std::to_string(index));
        check(rejects([&] { store.commit("unrelated-command"); }) && rejects([&] { store.close(); }) &&
            rejects([&] { store.checkpoint(); }) && rejects([&] { store.save(); }) && store.receipt("generation-2").is_null(),
            "Failed business commits stop checkpointing, dependent commands and writer close until acknowledged: " + std::to_string(index));
        // Simulate an erroneous caller changing mutable work data: retry still
        // publishes the frozen envelope rather than rerolling its RNG/rewards.
        stageGeneration(store, 99);
        store.setFailureInjector({});
        const auto receipt = index % 2 ? store.retryPending() : store.commit("generation-2");
        check(receipt["generation"] == 2 && !store.hasPendingCommit() && store.generation() == 2,
            "Retry commits the same generation identity once: " + std::to_string(index));
        store.close();
        CharacterStore recovered(path, content);
        const auto &c = recovered.data["characters"][0];
        check(c["progression"]["gold"] == 200 && c["progression"]["ledger"]["kill-A"] == 2 &&
            c["region_session"]["world"]["monster_hp"] == 0 && c["region_session"]["drops"]["claimed"] == true &&
            c["simulation"]["rng"]["loot"] == 246 && c["simulation"]["pending_events"][0]["id"] == 2,
            "World, inventory, reward ledger, RNG and pending event recover from the same frozen generation: " + std::to_string(index));
        check(recovered.receipt("generation-2") == receipt, "Retried receipt is durable after restart: " + std::to_string(index));
    }
    for (size_t index = 0; index < boundaries.size(); ++index) {
        const auto path = directory / ("checkpoint-failure-" + std::to_string(index));
        CharacterStore store(path, content);
        store.data = root(); stageGeneration(store, 1);
        const auto businessReceipt = store.commit("business-before-checkpoint");
        const auto receipts = store.data["_storage"]["receipts"];
        stageGeneration(store, 2);
        store.setFailureInjector([&](SaveFailurePoint point) { if (point == boundaries[index]) throw std::runtime_error("Injected checkpoint boundary failure"); });
        check(rejects([&] { store.checkpoint(); }) && store.hasPendingCommit(),
            "Checkpoint failure freezes the complete candidate: " + std::to_string(index));
        const auto disk = Json::parse(readFile(path / "characters.json"));
        check(disk["_storage"]["generation"] == (boundaries[index] == SaveFailurePoint::AfterPublish ? 2 : 1) &&
            disk["_storage"]["receipts"] == receipts && store.receipt("business-before-checkpoint") == businessReceipt,
            "Checkpoint failure exposes one complete generation without a new permanent receipt: " + std::to_string(index));
        check(rejects([&] { store.commit("business-after-checkpoint"); }) &&
            rejects([&] { store.commit("business-before-checkpoint"); }) && rejects([&] { store.close(); }),
            "Pending checkpoint cannot be bypassed by either a new or previously committed business request: " + std::to_string(index));
        stageGeneration(store, 99);
        store.setFailureInjector({});
        Json result;
        if (index % 3 == 0) result = store.checkpoint();
        else if (index % 3 == 1) { store.save(); result = store.data["_storage"]["result"]; }
        else result = store.retryPending();
        check(result["kind"] == "checkpoint" && result["request_id"].is_null() && result["generation"] == 2 &&
            !store.hasPendingCommit() && store.data["_storage"]["receipts"] == receipts &&
            store.data["characters"][0]["progression"]["gold"] == 200 &&
            store.data["characters"][0]["simulation"]["rng"]["loot"] == 246 &&
            store.data["characters"][0]["simulation"]["pending_events"][0]["id"] == 2,
            "Checkpoint retry reuses the frozen state through checkpoint, save or retryPending: " + std::to_string(index));
        store.close();
        CharacterStore recovered(path, content);
        check(recovered.generation() == 2 && recovered.data["_storage"]["result"] == result &&
            recovered.data["_storage"]["receipts"] == receipts && recovered.receipt("business-before-checkpoint") == businessReceipt &&
            recovered.data["characters"][0]["region_session"]["world"]["monster_hp"] == 0 &&
            recovered.data["characters"][0]["region_session"]["drops"]["claimed"] == true,
            "Retried checkpoint restores matching world, reward ledger and unchanged business receipts: " + std::to_string(index));
    }
    for (size_t index = 0; index < boundaries.size(); ++index) {
        const auto path = directory / ("crash-" + std::to_string(index));
        {
            CharacterStore store(path, content);
            store.data = root(); stageGeneration(store, 1); store.commit("previous");
            stageGeneration(store, 2);
            store.setFailureInjector([&](SaveFailurePoint point) { if (point == boundaries[index]) throw std::runtime_error("Simulated process exit"); });
            check(rejects([&] { store.commit("attempted"); }), "Crash fixture reaches storage boundary: " + std::to_string(index));
            // Destruction represents process loss: do not call retry or remove
            // the abandoned staged candidate. Recovery only reads published roots.
        }
        CharacterStore recovered(path, content);
        const bool published = boundaries[index] == SaveFailurePoint::AfterPublish;
        const int expected = published ? 2 : 1;
        const auto &c = recovered.data["characters"][0];
        check(recovered.generation() == uint64_t(expected) && c["progression"]["gold"] == expected * 100 &&
            c["simulation"]["rng"]["loot"] == expected * 123 &&
            c["simulation"]["pending_events"][0]["id"] == expected &&
            recovered.receipt("attempted").is_null() != published,
            "Restart ignores unpublished staging files and restores one complete generation: " + std::to_string(index));
    }
    for (size_t index = 0; index < boundaries.size(); ++index) {
        const auto path = directory / ("checkpoint-crash-" + std::to_string(index));
        Json receipt;
        {
            CharacterStore store(path, content);
            store.data = root(); stageGeneration(store, 1); receipt = store.commit("previous-business");
            stageGeneration(store, 2);
            store.setFailureInjector([&](SaveFailurePoint point) { if (point == boundaries[index]) throw std::runtime_error("Checkpoint process loss fixture"); });
            check(rejects([&] { store.save(); }), "Checkpoint crash fixture reaches storage boundary: " + std::to_string(index));
        }
        CharacterStore recovered(path, content);
        const bool published = boundaries[index] == SaveFailurePoint::AfterPublish;
        const int expected = published ? 2 : 1;
        const auto &saved = recovered.data["characters"][0];
        check(recovered.generation() == uint64_t(expected) && saved["progression"]["gold"] == expected * 100 &&
            saved["simulation"]["rng"]["loot"] == expected * 123 && saved["simulation"]["pending_events"][0]["id"] == expected &&
            recovered.data["_storage"]["kind"] == (published ? "checkpoint" : "business") &&
            recovered.data["_storage"]["receipts"].size() == 1 && recovered.receipt("previous-business") == receipt,
            "Checkpoint restart restores an entire published generation while preserving business idempotency: " + std::to_string(index));
    }
    {
        const auto path = directory / "corruption";
        CharacterStore store(path, content);
        store.data = root(); stageGeneration(store, 1); store.commit("one");
        stageGeneration(store, 2); store.commit("two"); store.close();
        auto damaged = Json::parse(readFile(path / "characters.json"));
        damaged["characters"][0]["progression"]["gold"] = 999999;
        atomicJson(path / "characters.json", damaged);
        const auto corruptBytes = readFile(path / "characters.json");
        CharacterStore recovered(path, content);
        check(recovered.generation() == 1 && recovered.data["characters"][0]["progression"]["gold"] == 100 && !recovered.warnings.empty(),
            "Parseable checksum corruption recovers the last complete valid backup");
        recovered.commit("repair"); recovered.close();
        bool preserved = false;
        for (const auto &file : fs::directory_iterator(path))
            if (file.path().filename().u8string().find("characters.rejected.") == 0)
                preserved = preserved || readFile(file.path()) == corruptBytes;
        check(preserved, "Repair archives corrupt original bytes and never rotates them into the good backup");
        CharacterStore repaired(path, content);
        check(repaired.data["characters"][0]["progression"]["gold"] == 100, "Repaired primary remains reloadable");
    }
    return {{"status", "pass"}, {"checks", checks}, {"check_count", checks.size()}, {"directory", directory.u8string()},
        {"scope", "OS writer exclusion, explicit source binding, schema/format migration, atomic checkpoint and business envelopes, stable receipts and injected failure recovery; no command execution/rollback, complete entity graph or filesystem power-loss proof"}};
}

Json runTransactionStorageWorldTests(Pvf &pvf, Assets &assets) {
    Json checks = Json::array();
    auto check = [&](bool condition, const std::string &message) {
        if (!condition) throw std::runtime_error("Transactional World save: " + message);
        checks.push_back(message);
    };
    const auto stamp = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    const auto path = fs::absolute(fs::path("cache/transaction-storage-world-tests") / std::to_string(stamp));
    CharacterStore store(path, "runtime-test-content");
    store.data = root();
    World world(pvf, assets);
    world.advance(1000000000);
    world.activate(0);
    check(world.remainingCd(0) > 0, "Live skill creates a cooldown before capture");
    // Create due work and a fractional clock boundary so restoration cannot
    // pass by merely selecting the same character in a reset World.
    world.advance(25000000, 0);
    world.enqueue({int64_t(3000000000), 27, true});
    world.idSources().requests.next();
    auto &loot = world.randomStreams().stream(RandomDomain::Loot, 51);
    loot.next(); loot.next();
    store.capture(0, world);
    const auto checkpoint = store.data["characters"][0]["simulation"];
    const int cooldown = world.remainingCd(0);
    const auto expectedDraw = loot.next();
    store.commit("runtime-boundary"); store.close();
    CharacterStore recovered(path, "runtime-test-content");
    const auto savedCharacter = recovered.data["characters"][0];
    World restored(pvf, assets);
    recovered.apply(0, restored);
    const auto loaded = restored.simulationCheckpoint();
    check(loaded["clock"] == checkpoint["clock"] && loaded["ids"] == checkpoint["ids"] &&
        loaded["effects"] == checkpoint["effects"] && loaded["random"] == checkpoint["random"],
        "CharacterStore capture/apply restores the actual World clock, IDs and domain RNG checkpoint");
    check(restored.remainingCd(0) == cooldown, "Skill cooldown restores after the simulation clock so remaining time is unchanged");
    check(restored.randomStreams().stream(RandomDomain::Loot, 51).next() == expectedDraw,
        "A real World continues the saved loot stream without replaying or rerolling draws");
    check(loaded["inputs"]["pending"].empty() && loaded["inputs"]["sequences"] == checkpoint["inputs"]["sequences"] &&
        restored.activeSkill() < 0 && !restored.armor() && !restored.invincible(),
        "Explicit transient cancellation removes saved input edges and action protection but keeps sequence identity");
    check(restored.pendingTicks() == world.pendingTicks(), "World catch-up debt survives the same atomic character snapshot");
    World live(pvf,assets);
    live.advance(500000000);
    live.activate(0);
    live.player.hp=37;live.player.x=519;
    Actor monster;monster.id=73;monster.hp=62;monster.x=700;live.monsters.push_back(monster);
    live.enqueue({2000000000,27,true});
    live.randomStreams().stream(RandomDomain::Combat,9).next();
    const auto stateBefore=live.snapshot(),simulationBefore=live.simulationCheckpoint(),ledgerBefore=live.skillState().snapshot(live.nowMs());
    const auto eventsBefore=live.eventLog(),inputsBefore=live.inputs();
    const auto identityBefore=live.identity();
    const auto activeBefore=live.activeSkill();
    std::vector<Json> invalid;
    auto corrupt=checkpoint;corrupt["clock"]["tick"]=-1;invalid.push_back(corrupt);
    corrupt=checkpoint;corrupt["ids"]["attacks"]["next"]=-1;invalid.push_back(corrupt);
    corrupt=checkpoint;corrupt["effects"]["next"]=uint64_t(std::numeric_limits<uint64_t>::max());invalid.push_back(corrupt);
    corrupt=checkpoint;corrupt["inputs"]["pending"][0]["payload"]["key"]=uint64_t(1)<<32;invalid.push_back(corrupt);
    corrupt=checkpoint;corrupt["random"]["schema"]=2;invalid.push_back(corrupt);
    corrupt=checkpoint;corrupt["entities"]["ids"]["next"]=0;invalid.push_back(corrupt);
    corrupt=checkpoint;corrupt["restore_policy"]="unknown-policy";invalid.push_back(corrupt);
    for(size_t i=0;i<invalid.size();++i) {
        recovered.data["characters"][0]["simulation"]=invalid[i];
        bool rejected=false;
        try{recovered.apply(0,live);}catch(const std::exception&){rejected=true;}
        check(rejected&&live.identity()==identityBefore&&live.activeSkill()==activeBefore&&
            live.snapshot()==stateBefore&&live.simulationCheckpoint()==simulationBefore&&
            live.skillState().snapshot(live.nowMs())==ledgerBefore&&live.eventLog()==eventsBefore&&live.inputs()==inputsBefore,
            "Malformed checkpoint preflight leaves live identity, controller, actors, clock, RNG, ledger and pending input unchanged: "+std::to_string(i));
    }
    recovered.data["characters"][0]["simulation"]=checkpoint;
    recovered.data["characters"][0]["skill_state"]["schema"]=999;
    bool badLedger=false;try{recovered.apply(0,live);}catch(const std::exception&){badLedger=true;}
    check(badLedger&&live.snapshot()==stateBefore&&live.simulationCheckpoint()==simulationBefore&&
        live.skillState().snapshot(live.nowMs())==ledgerBefore,
        "Malformed skill ledger also fails before live controller cancellation");
    std::vector<std::pair<std::string, Json>> malformedCharacters;
    const auto malformedCharacter = [&](const std::string &name, const std::function<void(Json &)> &change) {
        auto value = savedCharacter; change(value); malformedCharacters.emplace_back(name, std::move(value));
    };
    const auto activeKey = std::to_string(live.skills.front().id), passiveKey = live.passives.front().key;
    malformedCharacter("wide active level", [&](Json &value) { value["skills"][activeKey] = (uint64_t(1) << 32) + 1; });
    malformedCharacter("active level type", [&](Json &value) { value["skills"][activeKey] = "future-metadata-in-consumed-value"; });
    malformedCharacter("fractional active level", [&](Json &value) { value["skills"][activeKey] = 1.5; });
    malformedCharacter("skill container type", [](Json &value) { value["skills"] = Json::array(); });
    malformedCharacter("wide passive level", [&](Json &value) { value["passives"][passiveKey] = std::numeric_limits<uint64_t>::max(); });
    malformedCharacter("negative passive overflow", [&](Json &value) { value["passives"][passiveKey] = int64_t(std::numeric_limits<int>::min()) - 1; });
    malformedCharacter("passive level type", [&](Json &value) { value["passives"][passiveKey] = Json::object(); });
    malformedCharacter("passive container type", [](Json &value) { value["passives"] = Json::array(); });
    malformedCharacter("wide blood passive level", [](Json &value) { value["passives"]["bloodyvigorous"] = uint64_t(1) << 32; });
    malformedCharacter("wide bound skill ID", [](Json &value) { value["bindings"][0] = (uint64_t(1) << 32) + 46; });
    malformedCharacter("bound skill ID type", [](Json &value) { value["bindings"][0] = "46"; });
    malformedCharacter("null skill ledger", [](Json &value) { value["skill_state"] = nullptr; });
    malformedCharacter("array skill ledger", [](Json &value) { value["skill_state"] = Json::array(); });
    malformedCharacter("string skill ledger", [](Json &value) { value["skill_state"] = "unsupported"; });
    for (const auto &[name, value] : malformedCharacters) {
        recovered.data["characters"][0] = value;
        bool rejected = false;
        try { recovered.apply(0, live); } catch (const std::exception &) { rejected = true; }
        check(rejected && live.identity() == identityBefore && live.activeSkill() == activeBefore &&
            live.snapshot() == stateBefore && live.simulationCheckpoint() == simulationBefore &&
            live.skillState().snapshot(live.nowMs()) == ledgerBefore && live.eventLog() == eventsBefore && live.inputs() == inputsBefore,
            "Character field preflight leaves the active World unchanged on " + name);
    }
    auto extensionCharacter = savedCharacter;
    extensionCharacter["skills"]["future-skill-extension"] = {{"uninterpreted", Json::array({1, "x", nullptr})}};
    extensionCharacter["passives"]["future-passive-extension"] = {{"uninterpreted", true}};
    extensionCharacter["level"] = std::numeric_limits<uint64_t>::max();
    extensionCharacter["weapon"] = std::numeric_limits<uint64_t>::max();
    recovered.data["characters"][0] = extensionCharacter;
    recovered.apply(0, restored);
    check(restored.characterLevel == 99 && restored.weapon == 3,
        "Wide legacy level and weapon values clamp before integer narrowing");
    recovered.capture(0, restored);
    check(recovered.data["characters"][0]["skills"]["future-skill-extension"] == extensionCharacter["skills"]["future-skill-extension"] &&
        recovered.data["characters"][0]["passives"]["future-passive-extension"] == extensionCharacter["passives"]["future-passive-extension"] &&
        recovered.data["future_root"] == root()["future_root"],
        "Unknown root and skill extension metadata survive validation, application and recapture");
    recovered.data["characters"][0] = savedCharacter;
    recovered.data["characters"][0].erase("skill_state");
    recovered.apply(0, restored);
    check(restored.activeSkill() < 0 && restored.skillState().identity() == CharacterIdentity::fromJson(savedCharacter["identity"]),
        "Legacy saves without skill_state remain compatible");
    RegionCatalog catalog(pvf, assets);
    Progression progression(catalog), savedProgression(catalog);
    progression.state["gold"] = 317;
    progression.state["future_live_progression"] = {{"keep", true}};
    savedProgression.state["level"] = 7;
    savedProgression.state["gold"] = 10000;
    check(savedProgression.buy(2, 1106, 2).ok, "Saved progression fixture purchases source recovery items through the real shop operation");
    savedProgression.state["future_saved_progression"] = {{"keep", Json::array({2, 5, 2})}};
    savedProgression.state["cooldown_wall"]["future-cooldown-test"] = std::numeric_limits<int64_t>::max();
    const auto validProgression = savedProgression.state;
    const auto progressionBefore = progression.state;
    const auto equipmentBefore = std::array<int, 4>{live.characterLevel, live.weapon, live.equipmentAttack, live.equipmentDefense};
    const auto appearanceState = [](const CharacterAppearance &appearance) {
        Json result = {{"identity", appearance.identity.json()}, {"job", appearance.job},
            {"body_order", appearance.bodyOrder}, {"body_variation", appearance.bodyVariation()},
            {"issues", appearance.issues}, {"parts", Json::object()}};
        for (const auto &[slot, part] : appearance.parts) {
            auto &value = result["parts"][slot];
            value = {{"source", part.source.path}, {"job", part.job}, {"variation", part.variation},
                {"hide_equipment", part.hideEquipment}, {"hide_layers", part.hideLayers}, {"layers", Json::array()}};
            for (const auto &layer : part.layers)
                value["layers"].push_back({{"order", layer.order}, {"variation", layer.variation},
                    {"source", layer.sourcePath}, {"animation", layer.animationScript}, {"directory", layer.animationDirectory}});
        }
        return result;
    };
    const auto appearanceBefore = appearanceState(live.characterAppearance());
    const auto unchanged = [&] {
        return live.identity() == identityBefore && live.activeSkill() == activeBefore &&
            live.snapshot() == stateBefore && live.simulationCheckpoint() == simulationBefore &&
            live.skillState().snapshot(live.nowMs()) == ledgerBefore && live.eventLog() == eventsBefore && live.inputs() == inputsBefore &&
            progression.state == progressionBefore && appearanceState(live.characterAppearance()) == appearanceBefore &&
            std::array<int, 4>{live.characterLevel, live.weapon, live.equipmentAttack, live.equipmentDefense} == equipmentBefore;
    };
    std::vector<std::pair<std::string, Json>> malformedProgressions;
    const auto malformed = [&](const std::string &name, const std::function<void(Json &)> &change) {
        auto value = validProgression; change(value); malformedProgressions.emplace_back(name, std::move(value));
    };
    malformedProgressions.emplace_back("non-object progression", Json::array());
    malformed("inventory shape", [](Json &value) { value["inventory"] = Json::object(); });
    malformed("wide level", [](Json &value) { value["level"] = (uint64_t(1) << 32) + 7; });
    malformed("wide gold", [](Json &value) { value["gold"] = (uint64_t(1) << 32) + 317; });
    malformed("unsigned experience overflow", [](Json &value) { value["xp"] = std::numeric_limits<uint64_t>::max(); });
    malformed("exhausted inventory identity", [](Json &value) { value["inventory"][0]["uid"] = std::numeric_limits<int>::max(); });
    malformed("wide item identity", [](Json &value) { value["inventory"][0]["id"] = (uint64_t(1) << 32) + 27118; });
    malformed("wide stack count", [](Json &value) { value["inventory"][0]["count"] = (uint64_t(1) << 32) + 1; });
    malformed("wide durability", [](Json &value) { value["inventory"][0]["durability"] = uint64_t(1) << 32; });
    malformed("exhausted next identity", [](Json &value) { value["next_uid"] = std::numeric_limits<int>::max(); });
    malformed("invalid wall cooldown", [](Json &value) { value["cooldown_wall"]["bad"] = std::numeric_limits<uint64_t>::max(); });
    malformed("missing equipped UID", [](Json &value) { value["equipped"]["[weapon]"] = 700; });
    int unknownItem = std::numeric_limits<int>::max();
    while (catalog.item(unknownItem) && unknownItem > 1) --unknownItem;
    check(!catalog.item(unknownItem), "Unknown item fixture uses an ID absent from the selected source catalog");
    malformed("equipped unknown item", [&](Json &value) { value["inventory"][0]["id"] = unknownItem; });
    malformed("equipment slot mismatch", [](Json &value) {
        const auto uid = value["equipped"]["[weapon]"];
        value["equipped"] = {{"[coat]", uid}};
    });
    malformed("equipment stack exceeds source limit", [](Json &value) { value["inventory"][0]["count"] = 2; });
    const auto *starter = savedProgression.item(27118);
    check(starter && starter->durability < std::numeric_limits<int>::max(), "Source starter fixture has bounded durability");
    malformed("equipment durability exceeds source limit", [&](Json &value) { value["inventory"][0]["durability"] = starter->durability + 1; });
    const ItemDefinition *foreignEquipment = nullptr, *levelEquipment = nullptr;
    for (const auto &[shopId, shop] : catalog.shops) {
        for (const int item : shop.items) {
            const auto *definition = savedProgression.item(item);
            if (!definition || !definition->equipment || definition->slot.empty()) continue;
            if (!foreignEquipment && !equipmentAllowsJob(live.characterSource(), definition->source)) foreignEquipment = definition;
            if (!levelEquipment && definition->minimumLevel > 1 &&
                equipmentAllowsJob(live.characterSource(), definition->source) &&
                (definition->slot != "[weapon]" || definition->weapon >= 0)) levelEquipment = definition;
            if (foreignEquipment && levelEquipment) break;
        }
        if (foreignEquipment && levelEquipment) break;
    }
    check(foreignEquipment && levelEquipment, "Source shop definitions provide foreign-job and higher-level equipment fixtures");
    const auto addEquipment = [](Json &value, const ItemDefinition &definition) {
        value["inventory"].push_back({{"uid", 20}, {"id", definition.id}, {"count", 1}, {"durability", definition.durability}});
        value["equipped"][definition.slot] = 20;
    };
    malformed("equipment job restriction", [&](Json &value) { addEquipment(value, *foreignEquipment); });
    malformed("equipment minimum level", [&](Json &value) { value["level"] = 1; addEquipment(value, *levelEquipment); });
    for (const auto &[name, value] : malformedProgressions) {
        recovered.data["characters"][0] = savedCharacter;
        recovered.data["characters"][0]["progression"] = value;
        bool rejected = false;
        try { recovered.apply(0, live, progression); } catch (const std::exception &) { rejected = true; }
        check(rejected && unchanged(), "Progression preflight preserves live World, equipment and caller progression on " + name);
    }
    // Only this test-local catalog's parsed copy is faulted. No PVF bytes or
    // shared World source data are written. A source conversion error must be
    // discovered while preparing, before the active World is cancelled.
    auto *faultedSource = const_cast<Script *>(catalog.item(16400));
    check(faultedSource != nullptr, "Source equipment failure fixture resolves the registered quest belt");
    const auto originalSource = *faultedSource;
    bool iconFaulted = false;
    for (auto &field : faultedSource->fields) if (normalize(field.tag) == "[icon]" && field.values.size() >= 2) {
        field.values[1] = "invalid-frame-fixture"; iconFaulted = true;
    }
    recovered.data["characters"][0] = savedCharacter;
    auto faultedProgression = validProgression;
    faultedProgression["inventory"].push_back({{"uid", 20}, {"id", 16400}, {"count", 1}, {"durability", 0}});
    recovered.data["characters"][0]["progression"] = faultedProgression;
    bool sourceRejected = false;
    try { recovered.apply(0, live, progression); } catch (const std::exception &) { sourceRejected = true; }
    *faultedSource = originalSource;
    check(iconFaulted && sourceRejected && unchanged(), "Equipment source decoding failure leaves the active World and caller progression unchanged");
    recovered.data["characters"][0] = savedCharacter;
    auto validWithUnknown = validProgression;
    validWithUnknown["inventory"].push_back({{"uid", 20}, {"id", unknownItem}, {"count", 1}, {"future_item", "quarantine-preserved"}});
    recovered.data["characters"][0]["progression"] = validWithUnknown;
    Progression expected(progression);
    expected.load(validWithUnknown, 1, 0);
    const auto expectedAppearance = appearanceState(live.prepareEquipmentAppearance(expected, CharacterIdentity::fromJson(savedCharacter.at("identity"))));
    recovered.apply(0, live, progression);
    check(progression.state == expected.state && live.characterLevel == expected.level() &&
        live.weapon == expected.equippedWeapon() && live.equipmentAttack == expected.attackBonus() &&
        live.equipmentDefense == expected.defenseBonus() && appearanceState(live.characterAppearance()) == expectedAppearance,
        "Successful restore publishes the prepared progression, source appearance and equipment attributes together");
    check(progression.state["inventory"].back()["future_item"] == "quarantine-preserved" &&
        progression.state["future_saved_progression"] == validProgression["future_saved_progression"],
        "Unknown unequipped items and future progression metadata survive successful restore");
    const int potion = int(std::find_if(progression.state["inventory"].begin(), progression.state["inventory"].end(),
        [](const Json &entry) { return entry["id"] == 1106; }) - progression.state["inventory"].begin());
    const auto used = progression.usePotion(potion, 100, 1, 1000, 1, 1000);
    check(used.ok && progression.state["cooldowns"]["future-cooldown-test"] == 600100,
        "Prepared progression publication preserves deferred wall-clock cooldown rebasing");
    {
        World beta(pvf, assets, WorldRules::BetaFoundationV1);
        Progression betaProgression(catalog);
        beta.applyEquipment(betaProgression);
        beta.advance(500000000); beta.activate(0);
        beta.player.hp = 37; beta.player.x = 519;
        Actor target; target.id = 83; target.hp = 61; target.x = 700; beta.monsters.push_back(target);
        beta.enqueue({2000000000, 27, true});
        beta.randomStreams().stream(RandomDomain::Combat, 19).next();
        const auto before = beta.snapshot(), simulation = beta.simulationCheckpoint();
        const auto ledger = beta.skillState().snapshot(beta.nowMs()), events = beta.eventLog(), inputs = beta.inputs();
        const auto beforeProgression = betaProgression.state;
        // Fault only the owned parsed definition cache copied by restore.
        // CHR/PVF bytes, the catalog and the active World's sources stay intact.
        auto *definition = const_cast<ItemDefinition *>(betaProgression.item(27118));
        check(definition != nullptr, "Speed restore fault resolves an owned source equipment definition");
        const auto source = definition->source;
        bool faulted = false;
        if (!definition->source.fields.empty()) {
            auto &field = definition->source.fields.front();
            field.tag = "[attack speed]"; field.values = Json::array({"invalid-speed-fixture"}); faulted = true;
        }
        recovered.data["characters"][0] = savedCharacter;
        recovered.data["characters"][0]["progression"] = validProgression;
        bool rejected = false;
        try { recovered.apply(0, beta, betaProgression); } catch (const std::exception &) { rejected = true; }
        definition->source = source;
        check(faulted && rejected && beta.snapshot() == before && beta.simulationCheckpoint() == simulation &&
            beta.skillState().snapshot(beta.nowMs()) == ledger && beta.eventLog() == events && beta.inputs() == inputs &&
            betaProgression.state == beforeProgression,
            "Source equipment speed failure is rejected before live controller, actors, attributes, RNG or progression change");
        Progression expectedBeta(betaProgression);
        expectedBeta.load(validProgression, 1, 0);
        auto expectedAttributes = beta.prepareBaseAttributes(beta.identity(), expectedBeta.level());
        auto expectedSpeeds = beta.prepareCharacterSpeeds(expectedAttributes, expectedBeta);
        recovered.apply(0, beta, betaProgression);
        World control(pvf, assets, WorldRules::BetaFoundationV1);
        recovered.apply(0, control);
        control.applyBaseAttributes(std::move(expectedAttributes), AttributeRebuildReason::CharacterRestore);
        control.setCharacterAppearance(control.prepareEquipmentAppearance(expectedBeta, control.identity()));
        control.characterLevel = expectedBeta.level(); control.weapon = expectedBeta.equippedWeapon();
        control.equipmentAttack = expectedBeta.attackBonus(); control.equipmentDefense = expectedBeta.defenseBonus();
        control.applyCharacterSpeeds(std::move(expectedSpeeds));
        beta.combat = control.combat = false;
        beta.enqueue({beta.simulationNanoseconds(), 79, true});
        control.enqueue({control.simulationNanoseconds(), 79, true});
        beta.advance(500000000); control.advance(500000000);
        check(beta.player.x == control.player.x && beta.player.y == control.player.y &&
            beta.characterLevel == expectedBeta.level() && betaProgression.state == expectedBeta.state,
            "Successful beta storage restore publishes prepared speeds consumed by subsequent movement");
    }
    return {{"status", "pass"}, {"checks", checks}, {"check_count", checks.size()}, {"directory", path.u8string()},
        {"scope", "CharacterStore actual World checkpoint consumer, cooldown/RNG continuation and private progression/equipment restore preflight; transient action cancellation is explicit, complete persistent entity graphs remain future work"}};
}
} // namespace dnf

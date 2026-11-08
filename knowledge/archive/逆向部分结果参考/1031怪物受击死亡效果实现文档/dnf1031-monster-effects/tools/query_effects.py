"""Export a version-bound monster's visual dependency graph from the local 1031 client.

Python 3.11+, standard library only. No game process or old handoff is required.
The output is a dependency inventory, not an ACT/PTL behavioral interpreter.
"""
import argparse
from collections import defaultdict, deque
import hashlib
import json
from pathlib import Path
import posixpath
import struct

from lib.pvf_reader import Pvf, ScriptDecoder, file_hash
from lib.ani_structure import animation

ROOT = Path(__file__).resolve().parents[1]
SCRIPT_SUFFIXES = (".mob", ".act", ".als", ".ptl")
RESOURCE_SUFFIXES = SCRIPT_SUFFIXES + (".ani", ".img", ".wav", ".ogg", ".nut", ".obj", ".po")

def norm(value):
    # Match the C++ ASCII lowercase and lexical path normalization.
    value = value.replace("\\", "/")
    value = "".join(chr(ord(c) + 32) if "A" <= c <= "Z" else c for c in value)
    return posixpath.normpath(value)

def sha(data):
    return hashlib.sha256(data).hexdigest()

def write(path, value):
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_text(json.dumps(value, ensure_ascii=False, indent=2) + "\n", "utf-8")

class NpkIndex:
    def __init__(self, client):
        self.client = client
        self.entries = defaultdict(list)
        self.errors = []
        key = bytearray(b"puchikon@neople dungeon and fighter ")
        while len(key) < 255:
            key.append(b"DNF"[len(key) % 3])
        key.append(0)
        for folder in ("ImagePacks2", "SoundPacks"):
            for path in sorted((client / folder).glob("*")):
                if path.suffix.lower() != ".npk":
                    continue
                try:
                    with path.open("rb") as stream:
                        header = stream.read(20)
                        if len(header) != 20 or header[:16].rstrip(b"\0") != b"NeoplePack_Bill":
                            raise ValueError("NPK signature")
                        count = struct.unpack_from("<I", header, 16)[0]
                        if count > 1000000:
                            raise ValueError("NPK count")
                        table = stream.read(count * 264)
                        if len(table) != count * 264:
                            raise ValueError("NPK index truncated")
                        pending = []
                        for i in range(count):
                            offset, length = struct.unpack_from("<II", table, i * 264)
                            encrypted = table[i*264+8:(i+1)*264]
                            name = bytes(c ^ key[j] for j, c in enumerate(encrypted)).split(b"\0", 1)[0].decode("gbk")
                            if offset < 20 + count * 264 or offset + length > path.stat().st_size:
                                raise ValueError("NPK entry bounds")
                            pending.append((norm(name), dict(archive=path.relative_to(client).as_posix(),
                                                            offset=offset, length=length)))
                    for name, entry in pending:
                        self.entries[name].append(entry)
                except (ValueError, OSError, UnicodeError, struct.error) as exc:
                    self.errors.append(dict(archive=str(path), error=str(exc)))

    def candidates(self, path):
        name = norm(path)
        if name in self.entries:
            return name, self.entries[name]
        return "sprite/" + name, self.entries.get("sprite/" + name, [])

    def read(self, entry):
        with (self.client / entry["archive"]).open("rb") as stream:
            stream.seek(entry["offset"])
            data = stream.read(entry["length"])
        if len(data) != entry["length"]:
            raise ValueError("Truncated NPK member")
        return data

def img_index(data, requested):
    """Header/crop/link inventory only; C++ decodeImg supplies pixel decoding."""
    if len(data) < 32:
        raise ValueError("IMG header truncated")
    legacy = data.startswith(b"Neople Image File")
    if not legacy and data[:16].rstrip(b"\0") != b"Neople Img File":
        raise ValueError("IMG signature")
    index_length, version, count = struct.unpack_from("<Qii", data, 16)
    if version not in (1, 2, 4) or not 0 <= count <= 100000:
        raise ValueError("IMG version/count")
    at, palette_count = 32, 0
    if version == 4:
        palette_count = struct.unpack_from("<i", data, at)[0]
        if not 0 <= palette_count <= 65536:
            raise ValueError("IMG palette")
        at += 4 + palette_count * 4
    def length(frame):
        if frame["mode"] != 5:
            return frame["length"]
        t, w, h = frame["type"], frame["w"], frame["h"]
        if t >= 18:
            return ((w+3)//4) * ((h+3)//4) * (8 if t == 18 else 16)
        return w * h * (4 if t == 16 else 1 if palette_count and t == 14 and frame["mode"] == 6 else 2)
    frames, walked = [], 0
    for i in range(count):
        kind = struct.unpack_from("<i", data, at)[0]
        if kind == 17:
            row = dict(index=i, type=kind, link=struct.unpack_from("<i", data, at+4)[0])
            at += 8
            walked += 8
        else:
            values = struct.unpack_from("<9i", data, at)
            row = dict(zip(("type", "mode", "w", "h", "length", "x", "y", "fw", "fh"), values))
            row["index"] = i
            if not (14 <= kind <= 20 and 5 <= row["mode"] <= 7 and row["w"] >= 0 and row["h"] >= 0 and row["length"] >= 0):
                raise ValueError("IMG frame header")
            at += 36
            walked += 36
            if legacy and version == 1:
                row["data_offset"] = at
                at += length(row)
        if at > len(data):
            raise ValueError("IMG bounds")
        frames.append(row)
    if not legacy and index_length != walked:
        raise ValueError("IMG index size")
    if not (legacy and version == 1):
        for row in frames:
            if row["type"] != 17:
                row["data_offset"] = at
                at += length(row)
                if at > len(data):
                    raise ValueError("IMG pixel data bounds")
    results = []
    for wanted in sorted(set(requested)):
        if not 0 <= wanted < count:
            results.append(dict(requested=wanted, error="IMG frame out of range"))
            continue
        current, seen = wanted, set()
        while frames[current]["type"] == 17:
            if current in seen:
                raise ValueError("IMG link cycle")
            seen.add(current)
            current = frames[current]["link"]
            if not 0 <= current < count:
                raise ValueError("IMG link out of range")
        results.append(dict(requested=wanted, resolved=current, linked_indices=sorted(seen), header=frames[current]))
    return dict(version=version, frame_count=count, palette_count=palette_count, requested_frames=results,
                pixel_decode="source/src/resources.cpp: decodeImg; alpha validity must be checked after decoding")

class Exporter:
    def __init__(self, client, catalog):
        self.client, self.catalog = client, catalog
        for name, field in (("DNF.exe", "exe_sha256"), ("Script.pvf", "pvf_sha256")):
            if file_hash(client/name) != catalog["source"][field]:
                raise ValueError("1031 version mismatch: " + name)
        self.pvf = Pvf(client/"Script.pvf")
        self.decoder = None
        self.npk = NpkIndex(client)
        self.common = json.loads((ROOT/"evidence/common-death-resources.json").read_text("utf-8"))

    def common_images(self, output):
        requested = defaultdict(set)
        for palette in range(1, 30):
            requested[f"monster/common/m{palette:04d}.img"].update(range(4))
        def strings(value):
            if isinstance(value, str):
                yield value
            elif isinstance(value, list):
                for item in value:
                    yield from strings(item)
            elif isinstance(value, dict):
                for item in value.values():
                    yield from strings(item)
        for resource in self.common:
            for frame in resource["data"].get("frames", []):
                if frame.get("image"):
                    requested[norm(frame["image"])].add(frame["image_frame"])
            for value in strings(resource["data"]):
                if norm(value).endswith((".img", ".ogg", ".wav")):
                    requested[norm(value)]  # Preserve image/sound members even with no static frame.
        result = []
        for path, frames in sorted(requested.items()):
            member, candidates = self.npk.candidates(path)
            row = dict(path=path, member=member, candidates=candidates)
            if len(candidates) != 1:
                row["error"] = "Missing/ambiguous NPK member"
            else:
                data = self.npk.read(candidates[0])
                row.update(location=candidates[0], sha256=sha(data), size=len(data))
                if path.endswith(".img"):
                    try:
                        row["img"] = img_index(data, frames)
                    except (ValueError, struct.error) as exc:
                        row["error"] = str(exc)
            result.append(row)
        write(output/"common-images.json", dict(source=self.catalog["source"], resources=result,
              scope="All 29 palette IMG members plus static IMG/audio references of the 23 common-death resources; not all branches execute in this preview."))
        return result

    def graph(self, row, output, extract=False):
        if self.decoder is None:
            self.decoder = ScriptDecoder(self.pvf)
        nodes, edges, diagnostics = {}, [], []
        requested = defaultdict(set)
        pending = deque()
        def enqueue(path):
            path = norm(path)
            if path not in nodes:
                if len(nodes) >= 2048:
                    raise ValueError("Dependency node budget exceeded")
                nodes[path] = dict(path=path)
                pending.append(path)
        def edge(source, target, relation, **extra):
            edges.append(dict(source=source, target=norm(target), relation=relation, **extra))
            enqueue(target)
        def resolve(source, value):
            candidates = list(dict.fromkeys([norm(posixpath.join(posixpath.dirname(source), value)), norm(value), norm(posixpath.join("monster", value))]))
            found = [p for p in candidates if p in self.pvf.by_name]
            return candidates, found
        enqueue(row["path"])
        for state, plan in row["states"].items():
            if plan.get("entry"):
                edge(row["path"], plan["entry"], "compiled_state_entry", state=state, field_offset=plan["source_offset"])
            for track in plan["tracks"]:
                edge(track["source"], track["path"], "compiled_track", state=state, track=track)
        for common in self.common:
            edge(row["path"], common["path"], "common_death_inventory_not_all_executed")
        raw_die = row["die_effect"]
        if len(raw_die) == 1 and len(raw_die[0]) == 3 and all(type(v) is int for v in raw_die[0]):
            palette = raw_die[0][1]
            if 0 < palette <= 9999:
                image = f"monster/common/m{palette:04d}.img"
                requested[image].update(range(4))
                edge(row["path"], image, "palette_candidate_respect_omit_before_playback", omit=raw_die[0][2])
        while pending:
            path = pending.popleft()
            node = nodes[path]
            try:
                if path in self.pvf.by_name:
                    data = self.pvf.read(path)
                    entry = self.pvf.by_name[path]
                    node.update(storage="pvf", sha256=sha(data), size=len(data),
                                pvf_entry=entry, hash_basis="decrypted unpadded member bytes")
                    if extract:
                        destination = output/"resources/pvf"/path
                        destination.parent.mkdir(parents=True, exist_ok=True)
                        destination.write_bytes(data)
                    if path.endswith(".ani"):
                        decoded = animation(data)
                        globals_ = {p["node"]:p["value"] for p in decoded["globals"]}
                        durations = [next((p["value"] for p in f["properties"] if p["node"] == 12), globals_.get(12, 50)) for f in decoded["frames"]]
                        node.update(animation=decoded, frame_durations_ms=durations, duration_ms=sum(durations))
                        for frame in decoded["frames"]:
                            if frame["image"]:
                                image = norm(frame["image"])
                                requested[image].add(frame["image_frame"])
                                edge(path, image, "ani_image", frame=frame["frame"], img_frame=frame["image_frame"], offset=frame["offset"])
                        if path+".als" in self.pvf.by_name:
                            edge(path, path+".als", "auto_als")
                    elif path.endswith(SCRIPT_SUFFIXES):
                        decoded = self.decoder.script(path)
                        node["script"] = decoded
                        for field in decoded["fields"]:
                            for slot, value in enumerate(field["values"]):
                                if not isinstance(value, str) or not norm(value).endswith(RESOURCE_SUFFIXES):
                                    continue
                                suffix = posixpath.splitext(norm(value))[1]
                                if suffix in (".img", ".wav", ".ogg"):
                                    edge(path, norm(value), "script_reference_unexecuted_unless_supported", field_offset=field["offset"], tag=field["tag"], value_slot=slot)
                                    continue
                                candidates, found = resolve(path, value)
                                if len(found) == 1:
                                    edge(path, found[0], "script_reference_unexecuted_unless_supported", field_offset=field["offset"], tag=field["tag"], value_slot=slot, raw=value)
                                else:
                                    diagnostics.append(dict(source=path, tag=field["tag"], field_offset=field["offset"], raw=value, candidates=candidates, existing_candidates=found, error="Missing/ambiguous script resource"))
                else:
                    name, candidates = self.npk.candidates(path)
                    node.update(storage="npk", member=name, candidates=candidates)
                    if len(candidates) != 1:
                        raise ValueError("Missing/ambiguous NPK member")
                    data = self.npk.read(candidates[0])
                    node.update(sha256=sha(data), size=len(data), hash_basis="raw NPK member bytes", location=candidates[0])
                    if extract:
                        destination = output/"resources/npk"/name
                        destination.parent.mkdir(parents=True, exist_ok=True)
                        destination.write_bytes(data)
            except (ValueError, KeyError, OSError, struct.error) as exc:
                node["error"] = str(exc)
                diagnostics.append(dict(source=path, error=str(exc)))
        # A resource can be discovered before all consumers: resolve IMG frames last.
        for image, indices in requested.items():
            node = nodes[image]
            if node.get("storage") == "npk" and "location" in node:
                try:
                    node["img"] = img_index(self.npk.read(node["location"]), indices)
                except (ValueError, struct.error) as exc:
                    node["img_error"] = str(exc)
                    diagnostics.append(dict(source=image, error=str(exc)))
        graph = dict(schema_version=1, source=self.catalog["source"], monster=row, nodes=list(nodes.values()),
                     edges=edges, diagnostics=diagnostics, npk_index_errors=self.npk.errors,
                     scope="Full referenced resource inventory, with source offsets and raw fields; only catalog visual tracks and contract-supported effects are executed. Object/script dependencies may have diagnostics. Does not infer combat rules.")
        write(output/"graph.json", graph)
        return dict(path=row["path"], ids=row["ids"], nodes=len(nodes), edges=len(edges), diagnostics=len(diagnostics), output=str(output/"graph.json"))

def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--client", type=Path, required=True)
    selection = parser.add_mutually_exclusive_group(required=True)
    selection.add_argument("--id", type=int, help="monster.lst numeric ID")
    selection.add_argument("--path", help="exact MOB path")
    selection.add_argument("--examples", action="store_true", help="export six representative monsters in one session")
    selection.add_argument("--common", action="store_true", help="export all 29 palette and static shared-effect image/audio locations only")
    parser.add_argument("--out", type=Path, required=True)
    parser.add_argument("--extract", action="store_true", help="also export decrypted PVF and raw NPK members")
    args = parser.parse_args()
    catalog = json.loads((ROOT/"data/monsters.json").read_text("utf-8"))
    ids = () if args.common else (5001, 1, 61491, 56013, 59005, 62638) if args.examples else (args.id,)
    rows = []
    for monster_id in ids:
        found = [r for r in catalog["monsters"] if norm(r["path"]) == norm(args.path)] if args.path else [r for r in catalog["monsters"] if monster_id in r["ids"]]
        if len(found) != 1:
            parser.error(f"Expected one monster, found {len(found)} for {args.path or monster_id}")
        rows.append(found[0])
    exporter = Exporter(args.client.resolve(), catalog)
    try:
        summaries = [exporter.graph(row, args.out/str(row["ids"][0]) if args.examples else args.out, args.extract) for row in rows]
        for summary in summaries:
            summary["output"] = Path(summary["output"]).relative_to(args.out).as_posix()
        exporter.common_images(args.out)
        if not args.common:
            write(args.out/"summary.json", summaries)
        print(json.dumps(summaries, ensure_ascii=False, indent=2))
    finally:
        exporter.pvf.close()

if __name__ == "__main__":
    main()

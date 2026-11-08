cmake_minimum_required(VERSION 3.20)
project(dnf_cpp_project LANGUAGES C CXX)
set(DNF_CLIENT_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/../../DNF1031客户端" CACHE PATH "Read-only source client")
set(DNF_TOOLCHAIN_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/../../dnf-native-demo/third_party" CACHE PATH "Read-only compiler utilities")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(SKIP_INSTALL_ALL ON CACHE BOOL "" FORCE)
add_subdirectory(third_party/zlib-1.3.1 EXCLUDE_FROM_ALL)
set(SDL_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/third_party/SDL2-2.32.10/x86_64-w64-mingw32")
add_library(dnf_core)
include(cmake/CoreModules.cmake)
target_include_directories(dnf_core PUBLIC include third_party third_party/native-contracts/include "${CMAKE_BINARY_DIR}/third_party/zlib-1.3.1" third_party/zlib-1.3.1)
target_link_libraries(dnf_core PUBLIC zlibstatic)







































set(DNF_SQUIRREL_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/third_party/squirrel-3.1-dnf")
file(GLOB DNF_SQUIRREL_SOURCES CONFIGURE_DEPENDS "${DNF_SQUIRREL_ROOT}/squirrel/*.cpp")
add_library(dnf_squirrel_vm STATIC ${DNF_SQUIRREL_SOURCES})
target_include_directories(dnf_squirrel_vm PUBLIC "${DNF_SQUIRREL_ROOT}/include")
target_compile_definitions(dnf_squirrel_vm PUBLIC SQUNICODE SQINTEGER32 SQSTRINGHASH32 DNF_SQ_BUDGET SQ_EXCLUDE_DEFAULT_MEMFUNCTIONS)
target_compile_options(dnf_squirrel_vm PRIVATE -fwrapv -fno-strict-aliasing -include math.h)

set_source_files_properties(src/simulation/scripting/squirrel_host.cpp src/simulation/scripting/squirrel_platform_windows.cpp
    PROPERTIES COMPILE_OPTIONS "-fwrapv;-fno-strict-aliasing;-include;math.h")
target_link_libraries(dnf_core PUBLIC dnf_squirrel_vm bcrypt)
if(WIN32)
 target_compile_definitions(dnf_core PUBLIC NOMINMAX WIN32_LEAN_AND_MEAN)
endif()
add_executable(dnf_native src/app/main.cpp src/render/renderer.cpp src/render/font.cpp src/presentation/audio/audio.cpp src/presentation/ui/hud/hud.cpp src/presentation/ui/hud/target_hud.cpp src/presentation/ui/windows/region_ui.cpp src/presentation/ui/windows/equipment_ui.cpp)
target_sources(dnf_native PRIVATE src/diagnostics/debug_window.cpp)
target_sources(dnf_native PRIVATE src/presentation/ui/windows/skill_configuration_ui.cpp)
target_sources(dnf_native PRIVATE src/presentation/ui/windows/business_ui_render.cpp src/presentation/ui/windows/skill_learning_ui.cpp)
target_sources(dnf_native PRIVATE src/presentation/ui/windows/selection_ui.cpp src/app/sdl_text_input.cpp)
target_sources(dnf_native PRIVATE src/presentation/ui/windows/scene_presentation_ui.cpp)
target_include_directories(dnf_native PRIVATE "${SDL_ROOT}/include/SDL2")
target_compile_definitions(dnf_native PRIVATE SDL_MAIN_HANDLED)
target_link_libraries(dnf_native PRIVATE dnf_core "${SDL_ROOT}/lib/libSDL2.dll.a")
if(WIN32)
 target_link_libraries(dnf_native PRIVATE shell32 ole32)
endif()
if(WIN32)
 target_link_libraries(dnf_native PRIVATE gdi32)
endif()
add_custom_command(TARGET dnf_native POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different "${SDL_ROOT}/bin/SDL2.dll" "$<TARGET_FILE_DIR:dnf_native>")
add_executable(dnf_skill_preview src/tools/skill_preview.cpp src/render/renderer.cpp src/render/font.cpp)
target_include_directories(dnf_skill_preview PRIVATE "${SDL_ROOT}/include/SDL2")
target_compile_definitions(dnf_skill_preview PRIVATE SDL_MAIN_HANDLED)
target_link_libraries(dnf_skill_preview PRIVATE dnf_core "${SDL_ROOT}/lib/libSDL2.dll.a")
if(WIN32)
 target_link_libraries(dnf_skill_preview PRIVATE gdi32)
endif()
add_custom_command(TARGET dnf_skill_preview POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different "${SDL_ROOT}/bin/SDL2.dll" "$<TARGET_FILE_DIR:dnf_skill_preview>")
# Standalone skill-release viewer. Shares the resource scanner with the audit
# tool, but owns its own World-driven execution path.
set(DNF_SKILL_PREVIEWER_SOURCES
    src/tools/skill_preview_mapping.cpp
    src/tools/skill_preview_timeline.cpp
    src/tools/skill_preview_combat.cpp
    src/tools/skill_preview_particles.cpp
    src/tools/skill_preview_session.cpp
    src/tools/skill_preview_ui.cpp
    src/tools/skill_preview_audio.cpp
    src/render/renderer.cpp
    src/render/font.cpp
    src/presentation/audio/audio.cpp
    src/presentation/effects/boss_aura_ui.cpp)
add_executable(dnf_skill_previewer src/tools/skill_previewer_main.cpp ${DNF_SKILL_PREVIEWER_SOURCES})
target_include_directories(dnf_skill_previewer PRIVATE "${SDL_ROOT}/include/SDL2")
target_compile_definitions(dnf_skill_previewer PRIVATE SDL_MAIN_HANDLED)
target_link_libraries(dnf_skill_previewer PRIVATE dnf_core "${SDL_ROOT}/lib/libSDL2.dll.a")
if(WIN32)
 target_link_libraries(dnf_skill_previewer PRIVATE gdi32)
endif()
add_custom_command(TARGET dnf_skill_previewer POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different "${SDL_ROOT}/bin/SDL2.dll" "$<TARGET_FILE_DIR:dnf_skill_previewer>")

add_executable(dnf_skill_preview_tests tests/test_skill_preview.cpp ${DNF_SKILL_PREVIEWER_SOURCES})
target_include_directories(dnf_skill_preview_tests PRIVATE "${SDL_ROOT}/include/SDL2")
target_compile_definitions(dnf_skill_preview_tests PRIVATE SDL_MAIN_HANDLED)
target_link_libraries(dnf_skill_preview_tests PRIVATE dnf_core "${SDL_ROOT}/lib/libSDL2.dll.a")
if(WIN32)
 target_link_libraries(dnf_skill_preview_tests PRIVATE gdi32)
endif()
if(MINGW)
 target_link_options(dnf_skill_preview_tests PRIVATE -municode -static-libstdc++)
endif()
add_executable(dnf_audio_tests tests/audio_tests.cpp src/presentation/audio/audio.cpp)
add_executable(dnf_ui_tests tests/test_portal_renderer.cpp tests/test_long_ui_text.cpp tests/test_business_ui_runtime.cpp src/render/renderer.cpp src/render/font.cpp
    src/presentation/ui/windows/region_ui.cpp src/presentation/ui/windows/equipment_ui.cpp src/presentation/ui/windows/skill_learning_ui.cpp src/presentation/ui/windows/skill_configuration_ui.cpp src/presentation/ui/windows/business_ui_render.cpp)
target_sources(dnf_ui_tests PRIVATE src/presentation/ui/windows/selection_ui.cpp src/app/sdl_text_input.cpp tests/test_selection_ui.cpp tests/test_sdl_text_input.cpp)
target_sources(dnf_ui_tests PRIVATE src/presentation/ui/windows/scene_presentation_ui.cpp tests/test_scene_presentation_ui.cpp src/presentation/ui/hud/target_hud.cpp tests/test_world_presentation_runtime.cpp tests/test_character_advancement_ui.cpp)
target_include_directories(dnf_ui_tests PRIVATE "${SDL_ROOT}/include/SDL2")
target_compile_definitions(dnf_ui_tests PRIVATE SDL_MAIN_HANDLED)
target_link_libraries(dnf_ui_tests PRIVATE dnf_core "${SDL_ROOT}/lib/libSDL2.dll.a")
if(WIN32)
 target_link_libraries(dnf_ui_tests PRIVATE gdi32)
endif()
if(MINGW)
 target_link_options(dnf_ui_tests PRIVATE -municode -static-libstdc++)
endif()
target_include_directories(dnf_audio_tests PRIVATE "${SDL_ROOT}/include/SDL2")
target_compile_definitions(dnf_audio_tests PRIVATE SDL_MAIN_HANDLED DNF_AUDIO_TEST_STANDALONE)
target_link_libraries(dnf_audio_tests PRIVATE dnf_core "${SDL_ROOT}/lib/libSDL2.dll.a")
add_executable(dnf_tests tests/test_character_entry.cpp tests/test_monster_level_policy.cpp tests/test_core.cpp tests/test_character_catalog.cpp tests/test_character_controller.cpp tests/character_identity_tests.cpp tests/test_skill_data.cpp tests/test_dungeon_selection.cpp tests/test_objects.cpp tests/test_native_attack.cpp tests/test_animation_dynamics.cpp tests/test_animation_events.cpp tests/test_axis_motion.cpp tests/test_particle_motion.cpp tests/test_static_motion.cpp tests/test_skill_eligibility.cpp tests/test_region_progression.cpp tests/test_appearance.cpp tests/test_equipment_motion.cpp tests/test_skill_effects.cpp tests/monster_effects_tests.cpp tests/test_elvengard_flow.cpp tests/test_combat_feedback.cpp tests/test_user_feedback.cpp src/render/font.cpp)
target_link_libraries(dnf_tests PRIVATE dnf_core)
target_sources(dnf_tests PRIVATE tests/test_animation_clock.cpp)
target_sources(dnf_tests PRIVATE tests/test_scene_presentation.cpp tests/test_world_presentation_source.cpp tests/test_character_advancement.cpp)
target_sources(dnf_tests PRIVATE tests/test_character_advancement_cache.cpp)
target_sources(dnf_tests PRIVATE tests/test_beta_character.cpp)
target_sources(dnf_tests PRIVATE src/presentation/ui/windows/selection_ui.cpp tests/test_selection_ui.cpp tests/test_text_input.cpp tests/test_portal_visuals.cpp tests/test_portal_state.cpp)
target_sources(dnf_tests PRIVATE tests/test_effect_coordinates.cpp tests/test_female_gunner_timing.cpp tests/test_female_gunner_skill_layers.cpp)
target_sources(dnf_tests PRIVATE tests/test_skill_release_regression.cpp)
target_sources(dnf_tests PRIVATE tests/test_content_profile.cpp tests/test_content_catalog.cpp tests/test_simulation.cpp tests/test_transaction_storage.cpp)
target_sources(dnf_tests PRIVATE tests/test_session_layout.cpp)
target_sources(dnf_tests PRIVATE tests/test_skill_cost.cpp)
target_sources(dnf_tests PRIVATE tests/test_attributes.cpp tests/test_attributes_world.cpp)
target_sources(dnf_tests PRIVATE tests/test_speed_attributes.cpp tests/test_speed_world.cpp tests/test_debug.cpp tests/test_beta_branch.cpp
    tests/test_debug_window.cpp src/render/renderer.cpp src/diagnostics/debug_window.cpp)
target_sources(dnf_tests PRIVATE tests/test_equipment_attributes.cpp tests/test_equipment_resources_world.cpp
    tests/test_equipment_transaction.cpp tests/test_monster_attributes.cpp)
target_sources(dnf_tests PRIVATE tests/test_skill_learning.cpp tests/test_second_growtype_learning.cpp tests/test_skill_learning_storage.cpp
    tests/test_skill_learning_transaction.cpp tests/test_skill_learning_world.cpp tests/test_combat_attributes.cpp
    tests/test_monster_combat_attributes.cpp tests/test_damage_resolution.cpp tests/test_damage_world.cpp)
target_sources(dnf_tests PRIVATE tests/test_object_damage_world.cpp)
target_sources(dnf_tests PRIVATE tests/test_attack_status.cpp tests/test_status_world.cpp tests/test_status_room.cpp tests/test_act_runtime.cpp)
target_sources(dnf_tests PRIVATE tests/test_restore_handles.cpp)
target_sources(dnf_tests PRIVATE tests/test_act_world_host.cpp tests/test_act_collision.cpp)

target_sources(dnf_tests PRIVATE tests/test_monster_behavior.cpp tests/test_source_action_world.cpp)

target_sources(dnf_tests PRIVATE tests/test_monster_event_ai.cpp tests/test_monster_event_ai_world.cpp)
target_sources(dnf_tests PRIVATE tests/test_monster_event_ai_test_policy.cpp)
target_sources(dnf_tests PRIVATE tests/test_monster_event_ai_normal_policy.cpp)
target_sources(dnf_tests PRIVATE tests/test_runtime_paths.cpp)
target_sources(dnf_tests PRIVATE tests/test_map_access.cpp tests/test_map_exploration.cpp)

target_sources(dnf_tests PRIVATE tests/test_town_access.cpp)
target_sources(dnf_tests PRIVATE tests/test_map_exploration_world.cpp)
target_sources(dnf_tests PRIVATE tests/test_experimental_character.cpp tests/test_experimental_storage.cpp)
target_sources(dnf_tests PRIVATE tests/test_character_attack.cpp)
target_sources(dnf_tests PRIVATE tests/test_experimental_movement_reaction.cpp)
target_sources(dnf_tests PRIVATE tests/test_scene_camera.cpp)
target_sources(dnf_tests PRIVATE tests/test_map_rendering.cpp)

target_sources(dnf_tests PRIVATE tests/test_hud_source.cpp src/presentation/ui/hud/hud.cpp)
target_sources(dnf_tests PRIVATE tests/test_female_gunner_source.cpp tests/test_attack_status_dormant.cpp
    tests/test_status_effects.cpp tests/test_status_effects_world.cpp tests/test_female_gunner_world.cpp tests/test_female_gunner_contact_world.cpp tests/test_female_gunner_modifiers.cpp tests/test_female_gunner_heavy_layers.cpp
    src/presentation/ui/windows/business_ui_render.cpp src/presentation/ui/windows/skill_learning_ui.cpp src/presentation/ui/windows/region_ui.cpp src/presentation/ui/windows/equipment_ui.cpp)
target_sources(dnf_tests PRIVATE tests/test_squirrel_world_bridge.cpp tests/test_squirrel_action_service.cpp
    tests/test_skill_input_feedback.cpp)
target_include_directories(dnf_tests PRIVATE "${SDL_ROOT}/include/SDL2")
target_compile_definitions(dnf_tests PRIVATE SDL_MAIN_HANDLED)
target_link_libraries(dnf_tests PRIVATE "${SDL_ROOT}/lib/libSDL2.dll.a")
if(WIN32)
 target_link_libraries(dnf_tests PRIVATE gdi32)
endif()
enable_testing()
set(DNF_TEST_WORKER_ROOT "${CMAKE_BINARY_DIR}/test-workers")
foreach(group RANGE 0 11)
    file(MAKE_DIRECTORY "${DNF_TEST_WORKER_ROOT}/core-${group}")
    add_test(NAME "core_group_${group}"
        COMMAND dnf_tests "${DNF_CLIENT_ROOT}" --group "${group}")
    set_tests_properties("core_group_${group}" PROPERTIES
        WORKING_DIRECTORY "${DNF_TEST_WORKER_ROOT}/core-${group}")
endforeach()

if(MINGW)
 target_link_options(dnf_native PRIVATE -municode -static-libstdc++)
 target_link_options(dnf_skill_preview PRIVATE -municode -static-libstdc++)
 target_link_options(dnf_skill_previewer PRIVATE -municode -static-libstdc++)
 target_link_options(dnf_tests PRIVATE -municode -static-libstdc++)
 target_link_options(dnf_audio_tests PRIVATE -municode -static-libstdc++)
endif()

add_custom_command(TARGET dnf_native POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different "${DNF_TOOLCHAIN_ROOT}/llvm-mingw-20261006-ucrt-x86_64/bin/libunwind.dll" "$<TARGET_FILE_DIR:dnf_native>")
add_custom_command(TARGET dnf_skill_preview POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different "${DNF_TOOLCHAIN_ROOT}/llvm-mingw-20261006-ucrt-x86_64/bin/libunwind.dll" "$<TARGET_FILE_DIR:dnf_skill_preview>")
add_custom_command(TARGET dnf_skill_previewer POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different "${DNF_TOOLCHAIN_ROOT}/llvm-mingw-20261006-ucrt-x86_64/bin/libunwind.dll" "$<TARGET_FILE_DIR:dnf_skill_previewer>")

add_executable(dnf_inspect tools/inspect.cpp)
target_link_libraries(dnf_inspect PRIVATE dnf_core)
if(MINGW)
 target_link_options(dnf_inspect PRIVATE -municode -static-libstdc++)
endif()


target_sources(dnf_tests PRIVATE tests/test_monster_equipment.cpp)

# Source-indexed scene preparation and presentation consumers.

target_sources(dnf_tests PRIVATE tests/test_scene_preparation.cpp)

target_sources(dnf_native PRIVATE src/presentation/ui/windows/world_map_ui.cpp src/presentation/effects/boss_aura_ui.cpp)
target_sources(dnf_skill_preview PRIVATE src/presentation/effects/boss_aura_ui.cpp)
target_sources(dnf_ui_tests PRIVATE src/presentation/ui/windows/world_map_ui.cpp src/presentation/effects/boss_aura_ui.cpp)
target_sources(dnf_tests PRIVATE src/presentation/ui/windows/world_map_ui.cpp src/presentation/effects/boss_aura_ui.cpp tests/test_pvf_loading.cpp tests/test_monster_hurt_variation.cpp tests/test_object_presentation.cpp tests/test_female_gunner_release_origin.cpp)

target_sources(dnf_tests PRIVATE tests/test_female_gunner_jump_weapon.cpp)

target_sources(dnf_tests PRIVATE tests/test_female_gunner_source_cache.cpp tests/test_female_gunner_ammo_flight.cpp)


target_sources(dnf_tests PRIVATE tests/test_monster_action_ai.cpp)

target_sources(dnf_tests PRIVATE tests/test_basic_attack_movement.cpp)


target_sources(dnf_tests PRIVATE tests/test_watercannon_normal.cpp tests/test_watercannon_runtime.cpp tests/test_source_skill_actions.cpp tests/test_hedgehog_runtime.cpp tests/test_lowkick_runtime.cpp tests/test_mage_thrust_runtime.cpp tests/test_pickup_action.cpp)
target_sources(dnf_tests PRIVATE tests/test_gunner_knee_runtime.cpp tests/test_fighter_upper_runtime.cpp tests/test_fighter_native_grab.cpp)
target_sources(dnf_tests PRIVATE tests/test_monster_accuracy.cpp)
target_sources(dnf_tests PRIVATE tests/test_scene_tiles.cpp tests/test_gunner_basic_runtime.cpp tests/test_table_attack_miss.cpp tests/test_gunner_render_profile.cpp)
target_sources(dnf_ui_tests PRIVATE tests/test_scene_tiles_hidden.cpp)

target_sources(dnf_tests PRIVATE tests/test_selection_feedback_source.cpp)
target_sources(dnf_ui_tests PRIVATE tests/test_selection_feedback_runtime.cpp src/presentation/ui/hud/target_hud.cpp)




target_sources(dnf_tests PRIVATE tests/test_monster_damage_window.cpp)

# Persistent basic-dungeon reward intents and same-generation consumer checks.

target_sources(dnf_tests PRIVATE tests/test_pending_rewards.cpp)



target_sources(dnf_tests PRIVATE tests/test_normal_learning_bridge.cpp)
target_sources(dnf_ui_tests PRIVATE tests/test_normal_learning_ui_bridge.cpp)

# SDL physical-input acceptance remains at the native/UI boundary.
target_sources(dnf_native PRIVATE src/app/sdl_game_input.cpp)
target_sources(dnf_ui_tests PRIVATE src/app/sdl_game_input.cpp src/diagnostics/debug_window.cpp tests/test_pending_input_ui.cpp)

# Normal learning/runtime and real pending reward integration regression.
target_sources(dnf_tests PRIVATE tests/test_normal_reward_bridge.cpp)

# Application beta-exit lifecycle uses the same consumer in main and core tests.

target_sources(dnf_tests PRIVATE tests/test_beta_branch_exit.cpp)
target_sources(dnf_tests PRIVATE tests/test_priest_upper_runtime.cpp)

target_sources(dnf_tests PRIVATE tests/test_mage_upper_runtime.cpp)

# Application invocation state has explicit object ownership.
target_sources(dnf_native PRIVATE src/app/game_application.cpp)

# Source-backed composition is independent of SDL and shared by all render consumers.
target_sources(dnf_core PRIVATE
    src/presentation/characters/character_presentation.cpp
    src/diagnostics/frame_statistics.cpp)
add_executable(dnf_character_presentation_tests tests/test_character_presentation.cpp)
target_link_libraries(dnf_character_presentation_tests PRIVATE dnf_core)
if(MINGW)
    target_link_options(dnf_character_presentation_tests PRIVATE -municode -static-libstdc++)
endif()
add_executable(dnf_frame_statistics_tests tests/test_frame_statistics.cpp src/diagnostics/frame_statistics.cpp)
target_include_directories(dnf_frame_statistics_tests PRIVATE include)
if(MINGW)
    target_link_options(dnf_frame_statistics_tests PRIVATE -static-libstdc++)
endif()
add_test(NAME character_presentation COMMAND dnf_character_presentation_tests "${DNF_CLIENT_ROOT}")
add_test(NAME frame_statistics COMMAND dnf_frame_statistics_tests)
file(MAKE_DIRECTORY "${DNF_TEST_WORKER_ROOT}/character-presentation")
file(MAKE_DIRECTORY "${DNF_TEST_WORKER_ROOT}/frame-statistics")
file(MAKE_DIRECTORY "${DNF_TEST_WORKER_ROOT}/audio/reports")
file(MAKE_DIRECTORY "${DNF_TEST_WORKER_ROOT}/ui/reports/requested-ui")
set_tests_properties(character_presentation PROPERTIES
    WORKING_DIRECTORY "${DNF_TEST_WORKER_ROOT}/character-presentation")
set_tests_properties(frame_statistics PROPERTIES
    WORKING_DIRECTORY "${DNF_TEST_WORKER_ROOT}/frame-statistics")
add_test(NAME audio COMMAND dnf_audio_tests "${DNF_CLIENT_ROOT}" "${DNF_TEST_WORKER_ROOT}/audio/reports/audio-tests.json")
set_tests_properties(audio PROPERTIES WORKING_DIRECTORY "${DNF_TEST_WORKER_ROOT}/audio")
add_test(NAME ui COMMAND dnf_ui_tests "${DNF_CLIENT_ROOT}" "${DNF_TEST_WORKER_ROOT}/ui/reports/requested-ui")
set_tests_properties(ui PROPERTIES WORKING_DIRECTORY "${DNF_TEST_WORKER_ROOT}/ui")

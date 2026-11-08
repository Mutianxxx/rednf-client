# Preserved baseline tools

These scripts are unchanged mage-upper457 research/development tools. Relative
client/reverse paths and packaging assumptions have not all been migrated.
Do not use them as new-project entry points. The active tools are in ../.
The active builder only reuses package_playable.require_game_closed(), a
read-only process check; it does not invoke the legacy package command.

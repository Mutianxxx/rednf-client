#pragma once
#include <map>
#include <string>

namespace dnf {
inline const char *townMapAliasPackage1031() {
    return "d13ce454567197bb4617cad4d0e472f609a1ec5cf2256462d780547be878607d";
}
// 1031 source adapter, inferred from this PVF's complete TWN/MAP directory.
// Each literal below is absent and its listed (r) member exists. The older
// RegionCatalog already adapts Elvengard/Gate. This extends that explicit
// adapter, preserves both paths, and never aliases an existing source member.
// Recheck this version-specific table when changing content profiles.
inline const std::map<std::string,std::string> &townMapAliases1031() {
    static const std::map<std::string,std::string> aliases = {
        {"map/elvengard/gate.map","map/elvengard/(r)gate.map"},
        {"map/hendonmyre/hendon.map","map/hendonmyre/(r)hendon.map"},
        {"map/hendonmyre/gate_hendon.map","map/hendonmyre/(r)gate_hendon.map"},
        {"map/hendonmyre/westcoast.map","map/hendonmyre/(r)westcoast.map"},
        {"map/hendonmyre/westcoast_magic.map","map/hendonmyre/(r)westcoast_magic.map"},
        {"map/hendonmyre/gate_west.map","map/hendonmyre/(r)gate_west.map"},
        {"map/alfhlyra/gate_alfh.map","map/alfhlyra/(r)gate_alfh.map"},
        {"map/stormpass/gate_storm.map","map/stormpass/(r)gate_storm.map"},
        {"map/gent/gate_gent.map","map/gent/(r)gate_gent.map"},
        {"map/lufthafen/gate_lufthafent.map","map/lufthafen/(r)gate_lufthafent.map"},
        {"map/fair_pvp/gate_hendon.map","map/fair_pvp/(r)gate_hendon.map"},
        {"map/shonan/gate_shonan.map","map/shonan/(r)gate_shonan.map"},
        {"map/slough/gate_slough.map","map/slough/(r)gate_slough.map"},
        {"map/battleship/gate_battleship.map","map/battleship/(r)gate_battleship.map"}
    };return aliases;
}
} // namespace dnf

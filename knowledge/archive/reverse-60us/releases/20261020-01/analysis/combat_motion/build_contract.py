"""Generate the reviewable motion contract from byte manifest and vector reports."""
from pathlib import Path
import hashlib
import json

DEST = Path(__file__).resolve().parent


def main():
    evidence = json.loads((DEST / "evidence.json").read_text(encoding="utf-8"))
    vectors = json.loads((DEST / "native-vectors.json").read_text(encoding="utf-8"))
    ani_vectors = json.loads((DEST / "native-ani-vectors.json").read_text(encoding="utf-8"))
    contract = dict(
        schema="60US-combat-motion-contract/1",
        source_sha256=evidence["sha256"],
        pvf_sha256="23538ef1967baec4947c89ea0363cdce66230a3949b662faf54f7558673d7a98",
        authority="current native bytes first; no dnf-rebuild guesses used",
        scope="skill8/state22 movement setters, ordinary per-axis integration, callback collision boundary and ANI rate arithmetic",
        classification=dict(static_proven=["actor field writes", "virtual targets", "local-owner setter gates", "integer countdown formula",
                                           "axis integration and per-update clamp", "ordinary collision probe sequence", "ANI percent-rate consumers"],
                            extracted_native_executed=["50FDE0 free-axis original instructions with synthetic provider", "A2792F arithmetic slice with original C01544"],
                            original_client_runtime_observed=False),
        setup=dict(native_excerpt="0x00732c63..0x00732cda", axis0=[0, 600, 600, 0, -1000, 1],
                   axis1=[1, 0, 0, 0, 0, 0], mode=[2, 2, 1000, 1000, 1.0, 1.0],
                   direction=["current direction", 4, 0],
                   axis2="not written by these setters; preserve prior actor state",
                   effective_scale="S=max(1,trunc(float32(protected_int(stats+0x1f8))*protected_float(stats+0x200))) via mode2/4B55A0",
                   live_input_gate="both actor+1606/+1607 false; nonzero acceleration forces axis0 control flag false",
                   default_runtime_scale="unknown; S is caller input",
                   setter_order_caution="axis configuration precedes mode write; mode scale setter calls +49C to reapply current directions; supplied formula assumes local owner gate and final requested direction"),
        chain=[
            dict(va="0x004b9d80", role="virtual+488 actor per-axis config"),
            dict(va="0x004b99c0", role="virtual+498 apply direction and actor+1618 scale"),
            dict(va="0x00511040", role="gated velocity write"),
            dict(va="0x00511dd0", role="gated acceleration write; changed acceleration resets countdown to -1"),
            dict(va="0x00510d70", role="if V*A<0, remaining=trunc(V*(-1000)/A)"),
            dict(va="0x0049bec5", role="actor tick calls movement tick"),
            dict(va="0x00511400", role="paused check, elapsed delta, axis0/1/2 calls"),
            dict(va="0x0050fde0", role="velocity integration, displacement clamp, owner admissibility probes, position write"),
        ],
        actor_fields=[
            dict(offset="0x15d4+axis*8", kind="protected int", role="v1"),
            dict(offset="0x15e4+axis*8", kind="protected int", role="v2"),
            dict(offset="0x15f4+axis*8", kind="protected int", role="acceleration config"),
            dict(offset="0x1604+axis", kind="byte", role="deceleration countdown flag"),
            dict(offset="0x1606+axis", kind="byte", role="live input gate; forced false when acceleration nonzero"),
            dict(offset="0x1608+axis*4", kind="int", role="direction code"),
            dict(offset="0x1610/0x1614", kind="int", role="move/ANI mode"),
            dict(offset="0x1618/0x1620", kind="protected int", role="move/ANI scale"),
            dict(offset="0x1628/0x1630", kind="protected float", role="mode factors"),
        ],
        movement_object=dict(actor_pointer_offset="0xf8", provider="M[0] if nonnull else M+8",
                             provider_fields={"0x4+axis*4": "float32 position", "0x10+axis*4": "float32 velocity",
                                              "0x1c+axis*4": "int32 acceleration", "0x28+axis*4": "int32 remaining; -1 indefinite"},
                             fields={"0x74": "owner actor", "0x78": "external controller", "0x7c": "controller enabled byte",
                                     "0xa0": "timer", "0xe0": "paused byte", "0xe4": "last elapsed", "0xec/0xf0/0xf4": "per-axis result"}),
        axis_setup=dict(direction_sign={"0": -1, "1": 1, "2": -1, "3": 1, "4": 0},
                        factor="sign if S==1000 else float32(S*sign*float32(0.001))",
                        velocity="float32(selectedV*factor); selectedV is v2 iff both stored directions !=4, otherwise v1",
                        acceleration="int32(trunc(configAcceleration*factor))",
                        triple_slash="selectedV=600; configAcceleration=-1000; axis1 has V=A=0",
                        setter_gate="normal 511040/511DD0 only writes when 49C090(owner) true; model requires this as precondition"),
        clock=dict(source="winmm.dll!timeGetTime at IAT 0x0140f0d8",
                   chain=["B12AB0 advances selected percentage-scaled clock channels", "B12A80 selects channel value", "B06F00 applies timer active/paused/offset gates", "511400 dt=elapsed-first_query - M+E4; M+E4=elapsed-second_query"],
                   dt_unit="integer increments of a selected pausable/scaled gameplay clock derived from milliseconds",
                   input_precondition="dt>=0 signed int32; wrap/backwards clock not supported by model",
                   unresolved="actual runtime timer channel and rate/pauses for state22 are not observed; do not substitute wall time without binding",
                   fractional_carry="not claimed; B12AB0 plain branch subtracts stored accumulator itself after extracting increment"),
        integrate=dict(
            constant="k=float32(0.001)=0.0010000000474974513",
            branches=[
                "V==0 and A==0: return0 without changing position",
                "A==0: mean=V",
                "A!=0 and (R==-1 or dt<=R): Vn=f32(V+int32(A*dt)*k); mean=(V+Vn)*0.5; finite R-=dt; if R==0 set A=0",
                "A!=0 and 0<=R<dt: Vn=f32(V+int32(A*R)*k); earlymean=f32((V+Vn)*0.5); mean=(R*earlymean+(dt-R)*Vn)/dt; R=0; A=0",
                "d=f32(dt*mean*k), clamp d to [-2000,+2000] per invocation, not velocity",
            ],
            free_path="position=f32(position+d)",
            result_codes={"0": "zero velocity and acceleration", "1": "V*A<0 with A!=0", "2": "nonzero V and A==0", "3": "V*A>=0 with A!=0", "4": "ordinary owner probe rejected"},
            residual="expiry clears acceleration, not velocity; native vectors demonstrate tiny nonzero V and return2",
            x_of_t="execute step_axis repeatedly with actual dt sequence; trajectory depends on float32 stores and per-update clamp",
            ideal_approximation="ignoring stored rounding/clamp: T=min(t,R0*k), x=x0+V0*T+A0*T*T/2+(t-T)*(V0+A0*R0*k), with t=elapsed*k; for review illustration only"),
        collision=dict(
            free="owner null and controller disabled: no admissibility probe",
            ordinary_owner="controller null/disabled AND owner present: round positions via447FF0; step integer coordinate one unit at a time toward round(f32(position+d))",
            callback_xy="owner virtual+AC(newx,newy,&outCollisionObject)", callback_z="owner virtual+A8(newz)",
            rejection="write previous accepted integer coordinate; optionally owner virtual+274(axis,currentVelocity,collisionObject) if owner virtual+2C(1); return4",
            side_effect="50FDE0 updates V/A/R before probes; own helper does not clear them on collision; owner +274 may have extra effects",
            rounding="447FF0: trunc(x+H) when x>=0, trunc(x-H) otherwise; protected global H initialized0.5",
            external="M+78 nonnull and M+7c true: 50FDE0 skips ordinary owner probe; 511400 writes truncated provider coordinates into controller v+10 buffer, calls controller v+8, resolves mode/axis locks and owner callbacks",
            external_implementation="not closed; executable model raises NotImplementedError to avoid hiding this branch",
            unresolved="owner +A8/+AC/+274 bodies and concrete external controller type/normal state22 attachment not established"),
        ani=dict(
            stored_rate="ANI+0x134 is percent; 100 means nominal normal duration",
            refresh="4B9EB0: f32(Sani*float32(0.1)) applied to current body, attached actor+148 and flagged effects",
            installation="4B4DA0 / 4ACF80: f32(f32(Sani)*protected_global_float(1003404)*float32(0.001)); global initialized100.0 at CA1C00",
            path_difference="float32(0.1) and float32(0.001)*100 have different rounding; do not replace them with a single decimal ratio",
            zero_rate="A29C70 substitutes1.0 for effectively zero rate; for finite values the self-relative epsilon check only identifies zero",
            deadline="A2792F..4A: nextDeadline -= trunc(decodedSignedDelay / rate * float32(-100))",
            total_duration="A24BB0 separately sums trunc(decodedDelay*(1/rate)*float32(100)); multiplication order differs from deadline setter",
            rate_change="A29C70 root: reset tree, restore elapsed via trunc(oldElapsed/newRate*oldRate), reset/update frame; descendants receive new rate recursively",
            limits=["Decoded delay parser sign is not independently traced in this motion contract; example positive delays come from the PVF ANI artifacts.",
                    "Animation end and strict/inclusive frame advance boundaries must use the parent animation contract.",
                    "No fixed runtime Sani is asserted; periodic stat refresh may change rate mid-animation."]
        ),
        executable=dict(model="motion_model.py", example="example-motion.json",
                        original_code_verification="native_verify.py", original_ani_arithmetic_verification="native_ani_verify.py",
                        composition_verification="verify_contract.py", movement_matches=vectors["matches"],
                        movement_mismatches=vectors["mismatches"], ani_matches=ani_vectors["matches"],
                        ani_mismatches=ani_vectors["mismatches"],
                        assurance="recorded free-axis vectors match position/velocity/A/R/result bytes at x87 precision64 and53; no universal bit identity or original-client runtime claim"),
        remaining_gaps=["Concrete owner map-collision policy and +274 response effects",
                        "Concrete external controller class and whether ordinary state22 uses it",
                        "Actual runtime scale values, clock channel, clock rate, pause events and x87 control word",
                        "Full actor update ordering relative to rate refresh / state transitions / hit callbacks",
                        "ANI parser signed-delay write and animation end boundary integration"],
        artifacts=[dict(path=name, sha256=hashlib.sha256((DEST / name).read_bytes()).hexdigest())
                   for name in ["evidence.json", "motion_model.py", "native-vectors.json", "native-ani-vectors.json", "contract-checks.json"]],
    )
    (DEST / "motion-contract.json").write_text(json.dumps(contract, ensure_ascii=False, indent=2) + "\n", encoding="utf-8")
    print(json.dumps(dict(schema=contract["schema"], movement_vectors=vectors["matches"], ani_vectors=ani_vectors["matches"])))


if __name__ == "__main__":
    main()

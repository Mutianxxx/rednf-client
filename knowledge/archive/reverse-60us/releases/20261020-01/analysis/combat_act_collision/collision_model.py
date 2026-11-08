"""Current 60US CNRDAction move-collision trigger subset, with explicit gaps.

Produces calls at A49220. It does not execute behavior bodies or send messages.
The model accepts decoded native condition types, not other-version enums.
"""
from dataclasses import dataclass, field


@dataclass
class Condition:
    kind: int
    values: tuple = ()


@dataclass
class Trigger:
    conditions: list[Condition] = field(default_factory=list)
    count10: int = 0
    limit14: int = 0
    enabled18: bool = True
    blocked19: bool = False


def collision_calls(triggers, axis, *, owner_present=True, local_owner=True,
                    context_count=1, owner_v108=False):
    """A30D20 subset: types17,47,0,33,49 and wrong-event rejection.

    context_count models the context initialized by48E4F0. Other filters,
    count comparisons allowing empty contexts and behavior-side mutation raise
    rather than being guessed. Returns ordered A49220 boundary calls.
    """
    if not owner_present or not local_owner:
        return []
    axes = [True, True, False]  # initialized once per callback, not per trigger
    result = []
    for index, trigger in enumerate(triggers):
        if ((trigger.limit14 > 0 and trigger.count10 >= trigger.limit14)
                or trigger.blocked19 or not trigger.enabled18):
            continue
        collision_seen = False
        for condition in trigger.conditions:
            kind = condition.kind
            if kind in {6, 9, 10, 11, 12, 13, 14, 15, 16}:
                break  # abandon this trigger on the wrong event marker
            if kind == 17:
                collision_seen = True
                # A4A380 has no type17 filter; returns true with a context.
            elif kind == 47:
                selected = condition.values[0] if condition.values else -1
                if selected in (0, 1, 2):
                    axes = [selected == value for value in range(3)]
            elif kind in (0, 33, 49):
                if kind == 49 and not owner_v108:
                    continue
                if kind != 33:
                    if axis in (0, 1, 2):
                        collision_seen = axes[axis]
                        if not collision_seen:
                            continue
                    elif not collision_seen:
                        continue
                elif not collision_seen:
                    continue
                if context_count:
                    trigger.count10 = ((trigger.count10 + 1 + 0x80000000) & 0xffffffff) - 0x80000000
                    result.append(dict(trigger=index, condition_kind=kind,
                                       behavior=(condition.values[1] if len(condition.values) > 1 else -1),
                                       selector=(condition.values[0] if condition.values else -1),
                                       proc_flag=int(kind == 49)))
            else:
                raise NotImplementedError(f"ACT condition type {kind} is outside the collision subset")
    return result

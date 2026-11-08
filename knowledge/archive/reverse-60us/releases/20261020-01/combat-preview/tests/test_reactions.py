"""Regression checks for native ACT priority, fallback and unresolved boundaries."""
import hashlib
import json
from pathlib import Path
import sys
import types
import unittest

sys.path.insert(0,str(Path(__file__).resolve().parents[1]))
from pvf_model import parse_document
from reactions import MonsterRoutes

CONTRACT=json.loads((Path(__file__).resolve().parents[1]/'monster-contract.json').read_text(encoding='utf-8'))


class Scripts:
    def __init__(self, mob, act='[MOTION]\n[BASE ANI] `../ani/action.ani`\n[/MOTION]'):
        self.raw={'monster/test.mob':mob.encode('cp949'),
                  'monster/action/damage.act':act.encode('cp949'),
                  'monster/ani/motion.ani':b'', 'monster/ani/action.ani':b'',
                  'monster/ani/sit.ani':b'', 'monster/ani/waiting.ani':b''}
        self.pvf=types.SimpleNamespace(by_path=self.raw)
        self.source={'sha256':CONTRACT['source_pvf_sha256']}

    def document(self,path):return parse_document(self.raw[path],path)
    def identity(self,path):return {'path':path,'sha256':hashlib.sha256(self.raw[path]).hexdigest()}


class ReactionRouteTests(unittest.TestCase):
    def route(self,mob,state=3,variant=0,act=None):
        catalog=Scripts(mob,**({'act':act} if act is not None else {}))
        return MonsterRoutes(catalog,CONTRACT['source_exe_sha256']).route('monster/test.mob',state,variant)

    def test_action_wins_even_when_direct_motion_is_present(self):
        r=self.route('[damage motion 1] `ani/motion.ani`\n[damage action 1] `action/damage.act`')
        self.assertEqual(r['selection'],'action')
        self.assertEqual(r['animation_path'],'monster/ani/action.ani')
        base=r['candidates']['action']['base_ani']
        self.assertEqual(base['native_concatenation'],'monster/action/../ani/action.ani')
        self.assertIn('preview dot-segment',base['lookup_policy'])
        self.assertFalse(r['candidates']['action']['instructions_executed'])

    def test_damage_variant_is_zero_based(self):
        r=self.route('[damage motion 1] `ani/motion.ani`\n[damage motion 2] `ani/sit.ani`',variant=1)
        self.assertEqual(r['animation_path'],'monster/ani/sit.ani')
        self.assertEqual(r['role'],'damage2')

    def test_down_falls_back_to_sit_instead_of_waiting(self):
        r=self.route('[sit motion] `ani/sit.ani`\n[waiting motion] `ani/waiting.ani`',state=4)
        self.assertEqual(r['selection'],'sit_motion_fallback')
        self.assertEqual(r['animation_path'],'monster/ani/sit.ani')

    def test_existing_action_without_base_is_not_replaced_by_motion(self):
        r=self.route('[damage motion 1] `ani/motion.ani`\n[damage action 1] `action/damage.act`',
                     act='[MOTION]\n[/MOTION]')
        self.assertEqual(r['selection'],'action')
        self.assertIsNone(r['animation_path'])
        self.assertIn('不能回退',r['unresolved'])

    def test_damage_precondition_and_missing_resource_remain_unresolved(self):
        self.assertIsNone(self.route('[waiting motion] `ani/waiting.ani`')['animation_path'])
        r=self.route('[damage motion 1] `ani/motion.ani`\n[damage action 1] `missing.act`')
        self.assertIsNone(r['animation_path'])
        self.assertIn('加载失败',r['unresolved'])

    def test_repeated_resource_fields_are_not_silently_collapsed(self):
        with self.assertRaisesRegex(ValueError,'不唯一'):
            self.route('[damage motion 1] `ani/motion.ani`\n[damage motion 1] `ani/sit.ani`')

    def test_death_and_mismatched_source_are_rejected(self):
        with self.assertRaisesRegex(ValueError,'死亡'):
            self.route('',state=5)
        routes=MonsterRoutes(Scripts(''),'wrong-executable')
        with self.assertRaisesRegex(ValueError,'来源不符'):
            routes.route('monster/test.mob',3)


if __name__=='__main__':unittest.main()

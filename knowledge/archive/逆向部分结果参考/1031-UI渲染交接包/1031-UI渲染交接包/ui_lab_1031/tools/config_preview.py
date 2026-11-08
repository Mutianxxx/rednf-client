"""Evidence-bound offline CBT/EVN/WDM/STM preview specifications."""
import copy
import json
from common import ROOT, EXE_HASH, PVF_HASH, digest
from cbt_schema import decode_cbt, select_group, image_branch
from evn_schema import decode_evn, button_spec
from spatial_schema import decode_stm, decode_wdm
from preview_diagnostics import issue, diagnostics


def normalize(path):
    return path.replace('\\', '/').lower()


class ConfigLibrary:
    def __init__(self):
        self.configs = {}
        self.sources = {}
        self.resource_members = []
        folder = ROOT/'reports/followup-20261018'
        for kind, decoder in (('cbt', decode_cbt), ('evn', decode_evn), ('spatial', None)):
            path = folder/(kind+'-chain-evidence.json')
            verification = json.loads((folder/(kind+'-chain-verification.json')).read_text('utf8'))
            if not verification['passed'] or verification['evidence_sha256'] != digest(path):
                raise ValueError('Unverified configuration evidence: '+str(path))
            report = json.loads(path.read_text('utf8'))
            if report['exe_sha256'] != EXE_HASH or report['pvf_sha256'] != PVF_HASH:
                raise ValueError('Configuration evidence version mismatch')
            if kind == 'evn':
                selected = ROOT/'reports/session-analysis-20261018T071256-61396/selected-pvf-scripts.json'
                if digest(selected) != report['sources']['archived_scripts_sha256']:
                    raise ValueError('Archived EVN source hash mismatch')
                scripts = json.loads(selected.read_text('utf8'))['scripts']
                script = next(row for row in scripts if normalize(row['path']) == report['evn_member']['path'])
                if script['sha256'] != report['evn_member']['sha256']:
                    raise ValueError('EVN source differs from verified evidence')
                records = [dict(script=script)]
            else:
                records = report['scripts']
            for record in records:
                script = record.get('script', record.get('source'))
                parser = decoder or (decode_stm if script['path'].endswith('.stm') else decode_wdm)
                decoded = parser(script)
                key = normalize(decoded['path'])
                self.configs[key] = decoded
                self.sources[key] = dict(file=str(path.relative_to(ROOT)), sha256=digest(path),
                    member_sha256=script['sha256'], parser=parser.__module__)
            resources = report.get('resources', {})
            if kind == 'spatial':
                self.resource_members.extend(resources['physical_members'])
            elif kind == 'evn':
                self.resource_members.extend(dict(row, archive=resources['archive']['path']) for row in resources['members'])

    def view(self, path, catalog, *, group=1, branch=None, highlight=False, record=0,
             overview=False, state_slot=0, district=None):
        from preview import static_view
        path = normalize(path)
        decoded = self.configs[path]
        kind = path.rsplit('.', 1)[-1]
        issues = [issue('runtime_evidence', 'Configuration candidate; runtime visibility and business state are unobserved')]
        view = dict(mode='config', source=path, config_type=kind, candidate=True, static_controls=[],
            instances=[], images=[], clips=[], controls=[], draw_ops=[], configuration=copy.deepcopy(decoded),
            evidence=self.sources[path], selection=dict(group=group, record=record, overview=overview,
                state_slot=state_slot, highlight=highlight, district=district),
            capability=dict(identified=True, replayable=False, partial_replay=True,
                independently_rebuildable=False, locally_interactive=False))

        def sprite(image, frame, instance, position_x=0, position_y=0, **state):
            if not image:
                issues.append(issue('missing_resource',
                    'Numeric IMG manager mapping is unconfirmed: 00493770 protected entry and prior/repeated initialization unresolved; registration ordinal is not a verified vector index',
                    instance=instance, evidence='reports/remaining-followup/evidence.json', **state))
                return
            if frame < 0:
                issues.append(issue('unknown_state', 'Absent frame is not an IMG request', instance=instance, frame=frame))
                return
            physical = 'sprite/'+normalize(image) if not normalize(image).startswith('sprite/') else normalize(image)
            candidates = [row for row in self.resource_members if normalize(row['path']) == physical]
            if candidates and not any(frame < row['frames'] for row in candidates):
                issues.append(issue('missing_resource', 'Frame outside verified physical IMG range', path=image, frame=frame))
                return
            view['draw_ops'].append(dict(event='config_image', order=len(view['draw_ops']), path=image,
                frame=frame, x=position_x, y=position_y, instance=instance, state=state, physical_candidates=candidates,
                source_event=dict(configuration=path, evidence=self.sources[path])))

        if kind == 'cbt':
            effective = select_group(decoded, group)
            if effective is None:
                raise ValueError('Native CBT group must be 1..'+str(decoded['group_count']))
            predicate = dict(gate_0c=True, enabled_0d=True, alternate_34c=0, control_id=1,
                active_id=0, input_1b5650c=0, forced_id=0)
            predicate.update(branch or {})
            selected = image_branch(**predicate)
            view['selection'].update(branch=selected, predicate=predicate)
            if selected['slot'] is not None:
                sprite(effective['img_path'], effective['button_indices'][selected['slot']], path+':group:'+str(group),
                    img_index=effective['img_index'], native_group=group, branch=selected['branch'])
            elif selected['branch'] == 'alternate':
                issues.append(issue('unknown_state', '011C3180 alternate mode is not reconstructed'))
            if highlight and predicate['gate_0c'] and selected['branch'] != 'alternate' and effective['highlight_index'] >= 0:
                sprite(effective['img_path'], effective['highlight_index'], path+':highlight',
                    independent_highlight=True, img_index=effective['img_index'])
            issues.append(issue('unknown_state', 'CBT input names and actual runtime group are unconfirmed'))
        elif kind == 'evn':
            if type(record) is not int or not 0 <= record < decoded['group_count'] or state_slot not in range(4):
                raise ValueError('EVN record/state outside configured range')
            groups = decoded['groups'] if overview else [decoded['groups'][record]]
            view['tooltip_sources'] = []
            for index, entry in enumerate(groups):
                effective = entry['effective'];spec = button_spec(effective['id'], effective['image_start_index'])
                position_x, position_y = (280+20*(index % 12), 530-20*(index//12)) if overview else (0, 0)
                sprite(spec['path'], spec['input_frames'][state_slot], path+':record:'+str(entry['file_record']), position_x, position_y,
                    event_id=effective['id'], input_slot=state_slot, spec=spec)
                if highlight:
                    sprite(spec['path'], spec['highlight_frame'], path+':highlight:'+str(entry['file_record']), position_x, position_y,
                        independent_highlight=True)
                view['tooltip_sources'].extend(copy.deepcopy(field) for field in entry['fields'] if field['tag'] == '[tooltip]')
            view['layout_contract'] = 'configuration schematic: 004E7790, k is selected-list order; actual visible list unobserved' if overview else 'isolated record at preview origin'
            issues.append(issue('unknown_state', 'EVN business visibility, ID24 special path, dynamic tooltip and ANI clock unobserved'))
        elif kind == 'wdm':
            for role, ui in (('region', decoded['ui_path']), ('common', 'worldmap/ui/common/common.ui')):
                candidate = static_view(normalize(ui), catalog)
                for instance in candidate['instances']:
                    instance['instance'] = path+':'+role+':'+instance['instance']
                for control in candidate['static_controls']:
                    control['instance'] = path+':'+role+':'+control['instance']
                    control['key'] = path+':'+role+':'+control['key']
                    control['conditions'] = [(path+':'+role+':'+key, value) for key, value in control['conditions']]
                view['instances'].extend(candidate['instances'])
                view['static_controls'].extend(candidate['static_controls'])
                issues.extend(issue('unconfirmed_geometry', message, role=role) for message in candidate['missing'])
            view['resource_contexts'] = [dict(role='wdm map reference', path=decoded['map_image'], frame=decoded['map_frame'])]
            references={normalize(value) for control in view['static_controls'] for value in control['strings'] if value.lower().endswith('.img')}
            references.add(normalize(decoded['map_image']))
            for image in sorted(references):
                physical=image if image.startswith('sprite/') else 'sprite/'+image
                candidates=[row for row in self.resource_members if normalize(row['path'])==physical]
                view['resource_contexts'].append(dict(path=image,physical_candidates=candidates))
                if physical in ('sprite/worldmap/selectdungeon02_cn.img','sprite/worldmap/timegate.img'):
                    issues.append(issue('missing_resource','Unlocated map IMG; no substitute selected',path=physical))
            issues.append(issue('unknown_state', 'WDM dungeon conditions, balloon, switchbox and ACT scheduling unconfirmed'))
        elif kind == 'stm':
            sprite(decoded['map_image'], decoded['map_frame'], path+':main')
            stage_index = {}
            for area in decoded['areas']:
                for entry in area['districts']:
                    for ordinal, stage in enumerate(entry['stages'], 1):
                        stage_index[str(stage[0])] = dict(area_id=area['area_id'], district_id=entry['district_id'], ordinal=ordinal, raw_stage=stage)
                    if district is not None and entry['district_id'] == district:
                        sprite(entry['append_image'], entry['append_frame'], path+':district:'+str(district), area_id=area['area_id'], district_id=district)
            if district is not None and not any(row['district_id'] == district for row in stage_index.values()):
                raise ValueError('STM district outside configured range')
            view['stage_id_index'] = stage_index
            issues.append(issue('unknown_state', 'STM slot columns 2..5 and stage columns 2..4 have no verified draw consumer; retained raw'))
            issues.append(issue('unconfirmed_geometry', 'STM main/append alignment shown at preview origin; native placement unconfirmed'))
        if not decoded.get('schema_complete', all(entry.get('schema_complete', False) for entry in decoded.get('groups', []))):
            issues.append(issue('unknown_structure', 'Unrecognized fields retained in configuration'))
        view['preview_diagnostics'] = diagnostics(issues, support='partial configuration preview', native_visual_acceptance='pending')
        return view

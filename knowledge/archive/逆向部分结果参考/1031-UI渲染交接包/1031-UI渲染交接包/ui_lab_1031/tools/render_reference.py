"""Offline reference entry point; never loads the observer or calls game code."""
import argparse
import json
import math
import os
from pathlib import Path
import time
import common


def object_argument(value):
    raw = Path(value[1:]).read_text('utf-8-sig') if value.startswith('@') else value
    result = json.loads(raw)
    if not isinstance(result, dict):
        raise argparse.ArgumentTypeError('Expected a JSON object')
    return result


def render(args):
    os.environ.setdefault('QT_QPA_PLATFORM', 'offscreen')
    if args.command == 'render':
        if args.client:
            common.CLIENT = Path(args.client).resolve()
        common.verify_client(True)
    from PySide6 import QtCore, QtGui, QtWidgets
    from model import load_bundle
    from preview import Canvas, asset_key, animation_key, static_view
    application = QtWidgets.QApplication.instance() or QtWidgets.QApplication([])
    application.setFont(QtGui.QFont('Microsoft YaHei UI', 9))
    canvas = Canvas()
    service = None
    output = Path(args.out).resolve()
    if args.command == 'bundle' and output == Path(args.input).resolve():
        raise ValueError('Bundle output must differ from input')
    try:
        if args.command == 'bundle':
            manifest = load_bundle(args.input)
            if manifest['version'] != 1:
                raise ValueError('Unsupported offline bundle version')
            root = Path(args.input).resolve()
            canvas.assets = {key: dict(data, png=str(root/data['file']))
                             for key, data in manifest.get('assets', {}).items()}
            canvas.animations = manifest.get('animations', {})
            canvas.failures = dict(manifest.get('failures', {}))
            for key in manifest.get('unresolved_assets', []) + manifest.get('unresolved_animations', []):
                canvas.failures.setdefault(key, 'Unresolved in source offline bundle; no state invented')
            view, definitions = manifest['view'], manifest.get('definitions', [])
        else:
            from assets import Assets
            from config_preview import ConfigLibrary
            catalog = json.loads((common.ROOT/'catalog/index.json').read_text('utf8'))
            if (catalog['exe_sha256'], catalog['pvf_sha256']) != (common.EXE_HASH, common.PVF_HASH):
                raise ValueError('Catalog version mismatch')
            source = (args.ui or args.config).replace('\\', '/').lower()
            if args.ui:
                if not any(row['path'] == source for row in catalog['windows']):
                    raise ValueError('UI is not in the verified catalog: '+source)
                view = static_view(source, catalog)
            else:
                view = ConfigLibrary().view(source, catalog, group=args.group, branch=args.branch,
                    highlight=args.highlight, record=args.record, overview=args.overview,
                    state_slot=args.state_slot, district=args.district)
            service = Assets(output/'decode-cache')

            class Loader:
                def ask(self, path, frame):
                    key = asset_key(path, frame)
                    logical = path.replace('\\', '/').lower().removeprefix('sprite/')
                    choices = {name.replace('\\', '/').lower().removeprefix('sprite/'): archive
                               for name, archive in args.archive_map.items()}
                    try:
                        canvas.assets[key] = service.image(path, frame, choices.get(logical))
                    except Exception as error:
                        canvas.failures[key] = str(error)

                def ask_animation(self, path):
                    key = animation_key(path)
                    try:
                        canvas.animations[key] = service.animation(path)
                    except Exception as error:
                        canvas.failures[key] = str(error)

            canvas.worker = Loader()
            definitions = view.get('static_controls', [])
        saved_selection = view.get('reference_selection', {})
        canvas.tab_values.update(saved_selection.get('tabs', {}))
        canvas.tab_values.update(args.tabs)
        milliseconds = args.time_ms if args.time_ms is not None else saved_selection.get('external_time_ms', 0)
        looping = args.loop if args.loop is not None else saved_selection.get('external_loop', False)
        view['reference_selection'] = dict(tabs=dict(canvas.tab_values), external_time_ms=milliseconds, external_loop=looping)
        canvas.set_data(view, definitions, local=False)
        canvas.rebuild()
        canvas.rebuild()
        canvas.animation_timer.stop()
        canvas.animation_loop = looping
        canvas.animation_started = time.monotonic()-milliseconds/1000
        canvas.animate()
        bounds = canvas.scene().itemsBoundingRect().united(QtCore.QRectF(0, 0, 800, 600))
        left, top = math.floor(bounds.left()), math.floor(bounds.top())
        width, height = math.ceil(bounds.right())-left, math.ceil(bounds.bottom())-top
        if not 0 < width <= 4096 or not 0 < height <= 4096:
            raise ValueError('Reference output exceeds 4096 pixel safety bound; no silent resizing')
        canvas.export(output)
        image = QtGui.QImage(width, height, QtGui.QImage.Format_ARGB32)
        image.fill(QtGui.QColor('#20242c'))
        painter = QtGui.QPainter(image)
        try:
            canvas.scene().render(painter, QtCore.QRectF(0, 0, width, height),
                                  QtCore.QRectF(left, top, width, height))
        finally:
            painter.end()
        if not image.save(str(output/'preview.png')):
            raise OSError('Cannot save reference image')
        result = dict(source=view.get('source'), mode=view.get('mode', 'captured'),
            full_native_reconstruction=False, native_visual_acceptance='pending',
            image='preview.png', image_sha256=common.digest(output/'preview.png'),
            image_origin=[left, top], image_size=[width, height],
            external_time_ms=milliseconds, external_loop=looping,
            assets=len(canvas.assets), animations=len(canvas.animations),
            preview_diagnostics=canvas.view_data['preview_diagnostics'],
            limitation='Resource reconstruction only; unknown native layers/state remain explicit.')
        (output/'render-result.json').write_text(json.dumps(result, ensure_ascii=False, indent=2), 'utf8')
        print(json.dumps(dict(output=str(output), source=result['source'],
            full_native_reconstruction=False, summary=result['preview_diagnostics']['summary']), ensure_ascii=False))
    finally:
        if service:
            service.close()
        canvas.animation_timer.stop()
        canvas.worker = None
        canvas.close()


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    commands = parser.add_subparsers(dest='command', required=True)
    commands.add_parser('list')
    drawing = commands.add_parser('render')
    drawing.add_argument('--client')
    selection = drawing.add_mutually_exclusive_group(required=True)
    selection.add_argument('--ui')
    selection.add_argument('--config')
    drawing.add_argument('--group', type=int, default=1)
    drawing.add_argument('--branch', type=object_argument)
    drawing.add_argument('--highlight', action='store_true')
    drawing.add_argument('--record', type=int, default=0)
    drawing.add_argument('--overview', action='store_true')
    drawing.add_argument('--state-slot', type=int, choices=range(4), default=0)
    drawing.add_argument('--district', type=int)
    drawing.add_argument('--archive-map', type=object_argument, default={})
    bundle = commands.add_parser('bundle')
    bundle.add_argument('--input', required=True)
    for command in (drawing, bundle):
        command.add_argument('--out', required=True)
        command.add_argument('--tabs', type=object_argument, default={})
        command.add_argument('--time-ms', type=float)
        command.add_argument('--loop', action=argparse.BooleanOptionalAction, default=None)
    args = parser.parse_args()
    if args.command == 'list':
        from config_preview import ConfigLibrary
        catalog = json.loads((common.ROOT/'catalog/index.json').read_text('utf8'))
        print(json.dumps(dict(ui=[row['path'] for row in catalog['windows']],
            configurations=sorted(ConfigLibrary().configs), full_native_reconstruction=False),
            ensure_ascii=False, indent=2))
    else:
        if args.time_ms is not None and (not math.isfinite(args.time_ms) or args.time_ms < 0):
            parser.error('--time-ms must be finite and nonnegative')
        render(args)


if __name__ == '__main__':
    main()

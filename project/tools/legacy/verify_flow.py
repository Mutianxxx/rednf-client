"""Windows SDL acceptance through window keyboard/mouse messages, isolated saves.

No game-state writes, teleportation, god mode, forced kills or cooldown resets.
The live JSON is read-only observation. This test temporarily focuses its own window.
--appearance-fixture copies a core-generated isolated appearance save before launch;
that mode is rendering/equipment acceptance and does not claim normal acquisition.
"""
from pathlib import Path
from datetime import datetime, timezone
import ctypes as C
from ctypes import wintypes as W
import hashlib
import json
import subprocess
import time
import argparse
import shutil
import bisect
import heapq
import math
import traceback
from collections import deque
from test_window import show_test_window

root = Path(__file__).resolve().parents[1]
parser = argparse.ArgumentParser(description=__doc__)
parser.add_argument('--physical-keys', action='store_true', help='SendInput keyboard events; requires this game window to have foreground focus')
parser.add_argument('--binary', type=Path, default=root/'build/dnf_native.exe')
parser.add_argument('--ui-only', action='store_true', help='Capture creation, NPC dialogue, inventory and quest text through ordinary input, then stop before combat')
parser.add_argument('--settings-only', action='store_true', help='Verify volume/HP settings through ordinary UI, then exit and reload the isolated save')
parser.add_argument('--controls-only', action='store_true', help='Verify ordinary combo, jump, double-tap dash and return to normal attack in an isolated new character')
parser.add_argument('--appearance-fixture',action='store_true',help='Copy the isolated core appearance fixture, then verify outfit changes, preview, world poses and reload')
parser.add_argument('--unlearned-fixture', type=Path, help='Copy a core-generated zero-level skill save directory and verify rejection/reload through visible window input')
parser.add_argument('--deep',action='store_true',help='Normally clear Lorien to earn level2, turn in quest102/restock through Linus, then clear Lorien Inside with the same character')
parser.add_argument('--resolution',type=int,nargs=2,default=[800,600])
args = parser.parse_args()
if args.unlearned_fixture and any((args.deep, args.ui_only, args.appearance_fixture, args.settings_only, args.controls_only)):
    parser.error('--unlearned-fixture is a separate verification mode')
if args.deep and (args.ui_only or args.appearance_fixture or args.settings_only or args.controls_only):
    parser.error('--deep requires the ordinary combat flow')
if args.settings_only and (args.ui_only or args.appearance_fixture):
    parser.error('--settings-only is a separate UI verification mode')
if args.controls_only and (args.ui_only or args.appearance_fixture or args.settings_only):
    parser.error('--controls-only is a separate input verification mode')
binary = args.binary.resolve()
report = root / 'reports/runs' / (('appearance-' if args.appearance_fixture else 'physical-' if args.physical_keys else 'input-') + datetime.now(timezone.utc).strftime('%Y%m%dT%H%M%S'))
report.mkdir(parents=True)
saves = report / 'saves'
if args.appearance_fixture:
    fixture=json.loads((root/'reports/appearance-tests.json').read_text(encoding='utf-8'))
    source=(root/fixture['save_directory']).resolve()
    source.relative_to((root/'reports/test-saves/appearance').resolve())
    saves.mkdir()
    shutil.copy2(source/'characters.json',saves/'characters.json')
    (report/'fixture.json').write_text(json.dumps({'source':str(source),'scope':'core-generated visual/equipment fixture, not gameplay acquisition'},indent=2),encoding='utf-8')
if args.unlearned_fixture:
    source = args.unlearned_fixture.resolve()
    source.relative_to((root/'reports/test-saves/skill-eligibility').resolve())
    raw = (source/'characters.json').read_bytes()
    fixture = json.loads(raw)
    levels = fixture['characters'][0]['skills']
    assert len(levels) == 13 and all(value == 0 for value in levels.values()), 'Expected all 13 core fixture active levels to be zero'
    saves.mkdir()
    shutil.copy2(source/'characters.json', saves/'characters.json')
    (report/'fixture.json').write_text(json.dumps({'source':str(source),
        'source_sha256':hashlib.sha256(raw).hexdigest(), 'scope':'Core-generated zero-level active skill fixture, copied before process launch; no runtime state edits'},indent=2),encoding='utf-8')
binary_sha256 = hashlib.sha256(binary.read_bytes()).hexdigest()
user_saves = {p.name: hashlib.sha256(p.read_bytes()).hexdigest() for p in (root / 'saves').glob('*') if p.is_file()}
(report/'user-save-hashes-before.json').write_text(json.dumps(user_saves,indent=2),encoding='utf-8')
u = C.windll.user32
u.SetProcessDPIAware()
u.GetForegroundWindow.restype = W.HWND
u.PostMessageW.argtypes = [W.HWND, W.UINT, W.WPARAM, W.LPARAM]
u.SetForegroundWindow.argtypes = [W.HWND]
u.SetCursorPos.argtypes = [C.c_int,C.c_int]
original_cursor=W.POINT();u.GetCursorPos(C.byref(original_cursor))
u.GetClientRect.argtypes = [W.HWND, C.POINTER(W.RECT)]
u.ClientToScreen.argtypes = [W.HWND, C.POINTER(W.POINT)]
u.GetWindowThreadProcessId.argtypes = [W.HWND, C.POINTER(W.DWORD)]
u.AttachThreadInput.argtypes = [W.DWORD, W.DWORD, W.BOOL]
u.GetKeyboardLayout.argtypes = [W.DWORD]
u.GetKeyboardLayout.restype = W.HKL
u.LoadKeyboardLayoutW.argtypes = [W.LPCWSTR, W.UINT]
u.LoadKeyboardLayoutW.restype = W.HKL
u.SendMessageW.argtypes = [W.HWND, W.UINT, W.WPARAM, W.LPARAM]
class KeyboardInput(C.Structure):
    _fields_ = [('vk', W.WORD), ('scan', W.WORD), ('flags', W.DWORD), ('time', W.DWORD), ('extra', C.c_size_t)]
class MouseInput(C.Structure):
    _fields_ = [('dx', W.LONG), ('dy', W.LONG), ('data', W.DWORD), ('flags', W.DWORD), ('time', W.DWORD), ('extra', C.c_size_t)]
class HardwareInput(C.Structure):
    _fields_ = [('message', W.DWORD), ('low', W.WORD), ('high', W.WORD)]
class InputData(C.Union):
    _fields_ = [('keyboard', KeyboardInput), ('mouse', MouseInput), ('hardware', HardwareInput)]
class Input(C.Structure):
    _fields_ = [('type', W.DWORD), ('data', InputData)]
u.SendInput.argtypes = [W.UINT, C.POINTER(Input), C.c_int]
u.SendInput.restype = W.UINT
steps = []
process = None
window = None
held = set()
navigation_steps = []
supply_actions = []
dungeon_runs = []
result_panel_actions = []
# Current PC definitions, used only to locate ordinary UI inventory cells.
# Item 1047 is a fate coin, not a recovery item, and is never consumed here.
POTIONS = {1055: {'hp':110,'mp':0,'group':'group:2'},
           1004: {'hp':0,'mp':70,'group':'group:1'},
           1106: {'hp':70,'mp':0,'group':'group:0'},
           1112: {'hp':0,'mp':65,'group':'group:1'}}

class UiReviewComplete(Exception):
    pass

def launch(suffix=''):
    global process, window
    launch_args = [str(binary), '--save-dir', str(saves), '--report-dir', str(report/suffix),
            '--run-id', report.name+suffix, '--resolution', *map(str,args.resolution), '--trace', '--quit-after', '900']
    process = subprocess.Popen(launch_args, cwd=root, stdout=(report/('stdout'+suffix+'.log')).open('w'),
                               stderr=(report/('stderr'+suffix+'.log')).open('w'))
    window = None
    callback = C.WINFUNCTYPE(W.BOOL, W.HWND, W.LPARAM)
    @callback
    def visit(hwnd, _):
        global window
        pid = W.DWORD()
        u.GetWindowThreadProcessId(hwnd, C.byref(pid))
        if pid.value == process.pid and u.IsWindowVisible(hwnd): window = hwnd
        return True
    deadline = time.monotonic()+15
    while window is None and time.monotonic()<deadline:
        u.EnumWindows(visit, 0)
        if process.poll() is not None: raise RuntimeError('Application exited during startup')
        time.sleep(.1)
    if not window: raise RuntimeError('No visible SDL window')
    shown = show_test_window(process)
    (report/('test-window'+suffix+'.json')).write_text(json.dumps(shown,indent=2),encoding='utf-8')
    time.sleep(.25)
    if args.physical_keys:
        focus_game()
        # Select an English layout for this game's thread only. IME behavior is
        # intentionally outside this acceptance run; do not change global layout.
        english = u.LoadKeyboardLayoutW('00000409', 0)
        if not english: raise RuntimeError('English test keyboard layout unavailable')
        u.SendMessageW(window, 0x50, 0, english)  # WM_INPUTLANGCHANGEREQUEST
        thread = u.GetWindowThreadProcessId(window, None)
        layout = u.GetKeyboardLayout(thread)
        if (layout & 0xffff) != 0x409: raise RuntimeError('Game thread did not select English layout')
        (report/('keyboard'+suffix+'.json')).write_text(json.dumps({
            'input': 'SendInput scan codes', 'foreground_verified': u.GetForegroundWindow()==window,
            'game_thread_layout': hex(layout), 'ime_coverage': False,
            'layout_scope': 'game window thread; no global layout switch'
        },indent=2),encoding='utf-8')

def focus_game():
    if u.GetForegroundWindow()==window: return
    current = C.windll.kernel32.GetCurrentThreadId()
    foreground_thread = u.GetWindowThreadProcessId(u.GetForegroundWindow(), None)
    attached = bool(foreground_thread and foreground_thread != current and u.AttachThreadInput(current,foreground_thread,True))
    try:
        u.SetForegroundWindow(window)
        time.sleep(.1)
    finally:
        if attached: u.AttachThreadInput(current,foreground_thread,False)
    if u.GetForegroundWindow()!=window:
        raise RuntimeError('Physical input stopped: test game does not have foreground focus')

def state(suffix=''):
    if process.poll() is not None: raise RuntimeError('Application exited: '+str(process.returncode))
    try: return json.loads((report/suffix/'live.json').read_text(encoding='utf-8'))
    except (FileNotFoundError, PermissionError, json.JSONDecodeError): return None

def wait(predicate, seconds=12, suffix=''):
    deadline=time.monotonic()+seconds
    while time.monotonic()<deadline:
        j=state(suffix)
        if j and predicate(j): return j
        time.sleep(.04)
    raise RuntimeError('State timeout: '+str(state(suffix)))

def key(code, down=True):
    if isinstance(code,str): code=ord(code.upper())
    if args.physical_keys:
        focus_game()
        flags = 0x8 | (0 if down else 0x2)  # SCANCODE / KEYUP
        if code in (0x25,0x26,0x27,0x28): flags |= 0x1  # EXTENDEDKEY
        event = Input(1, InputData(keyboard=KeyboardInput(0,u.MapVirtualKeyW(code,0),flags,0,0)))
        if u.SendInput(1,C.byref(event),C.sizeof(Input)) != 1:
            raise RuntimeError('Physical keyboard injection failed')
        if down: held.add(code)
        else: held.discard(code)
        return
    if down:
        held.add(code)
    else: held.discard(code)
    scan=u.MapVirtualKeyW(code,0)
    flags=1 | (scan<<16) | (0 if down else (1<<30)|(1<<31))
    if code in (0x25,0x26,0x27,0x28): flags |= 1<<24
    if not u.PostMessageW(window,0x100 if down else 0x101,code,flags): raise RuntimeError('Key message delivery failed')

def tap(code, delay=.06):
    key(code); time.sleep(delay); key(code,False); time.sleep(.08)

def click(x,y,right=False):
    if u.GetForegroundWindow()!=window: u.SetForegroundWindow(window); time.sleep(.15)
    rect=W.RECT(); u.GetClientRect(window,C.byref(rect))
    scale=min(rect.right/800,rect.bottom/600)
    cx=int((rect.right-800*scale)/2+x*scale);cy=int((rect.bottom-600*scale)/2+y*scale)
    point=W.POINT(cx,cy); u.ClientToScreen(window,C.byref(point))
    u.SetCursorPos(point.x,point.y)
    xy=cx|(cy<<16)
    u.PostMessageW(window,0x200,0,xy)
    u.PostMessageW(window,0x204 if right else 0x201,2 if right else 1,xy);time.sleep(.07);u.PostMessageW(window,0x205 if right else 0x202,0,xy)
    time.sleep(.2)

def release():
    for code in list(held): key(code,False)

def record(name,suffix='',hover=None):
    j=wait(lambda x:True,suffix=suffix)
    steps.append({'name':name,'state':j})
    if hover is not None:
        # A selection click and F12 share the event batch. The environment may
        # refuse desktop cursor focus; this still exercises ordinary SDL item
        # selection and its actual tooltip drawing, without a state-write hook.
        rect=W.RECT();u.GetClientRect(window,C.byref(rect));scale=min(rect.right/800,rect.bottom/600)
        hx=int((rect.right-800*scale)/2+hover[0]*scale);hy=int((rect.bottom-600*scale)/2+hover[1]*scale)
        xy=hx|(hy<<16)
        u.PostMessageW(window,0x200,0,xy);u.PostMessageW(window,0x201,1,xy)
        tap(0x7b)
        u.PostMessageW(window,0x202,0,xy)
    else:tap(0x7b)  # F12, application's actual framebuffer capture
    time.sleep(.15)
    path=report/suffix/'manual.png'
    if path.exists(): (report/(name+'.png')).write_bytes(path.read_bytes())
    (report/'steps.json').write_text(json.dumps(steps,indent=2),encoding='utf-8')
    print(name, j['location'], j['room'], 'HP',j['world']['hp'],flush=True)

def move_until(predicate,code,seconds=10):
    key(code)
    try: return wait(predicate,seconds)
    finally: key(code,False); time.sleep(.1)


class GroundNavigation:
    """Observe World's rectangles; only the ordinary key driver moves anything.

    Rectangles are x/y/width/height. The closed blocker and ground boundaries,
    x=12..map_width-12 and the empty-ground fallback match World::canWalk.
    Axis-aligned segment tests use interval coverage rather than sampling, so
    a thin blocker or gap cannot be skipped between two A* nodes.
    """
    def __init__(self, observed):
        self.width = float(observed['map_width'])
        self.ground = [tuple(map(float, r)) for r in observed['walk_rects']]
        self.blocked = [tuple(map(float, r)) for r in observed['blocked_rects']]
        if not self.ground:
            self.ground = [(12., 185., self.width-24., 155.)]

    def walkable(self, point):
        x, y = point
        if not math.isfinite(x+y) or x < 12 or x > self.width-12:
            return False
        if any(bx <= x <= bx+bw and by <= y <= by+bh for bx, by, bw, bh in self.blocked):
            return False
        return any(rx <= x <= rx+rw and ry <= y <= ry+rh for rx, ry, rw, rh in self.ground)

    def clear(self, start, end):
        if not self.walkable(start) or not self.walkable(end):
            return False
        if abs(start[1]-end[1]) < 1e-7:
            lo, hi = sorted((start[0], end[0])); fixed = start[1]
            if any(by <= fixed <= by+bh and max(lo,bx) <= min(hi,bx+bw)
                   for bx,by,bw,bh in self.blocked):
                return False
            intervals = [(rx,rx+rw) for rx,ry,rw,rh in self.ground if ry <= fixed <= ry+rh]
        elif abs(start[0]-end[0]) < 1e-7:
            lo, hi = sorted((start[1], end[1])); fixed = start[0]
            if any(bx <= fixed <= bx+bw and max(lo,by) <= min(hi,by+bh)
                   for bx,by,bw,bh in self.blocked):
                return False
            intervals = [(ry,ry+rh) for rx,ry,rw,rh in self.ground if rx <= fixed <= rx+rw]
        else:
            return False
        covered = lo
        for lower, upper in sorted(intervals):
            if upper < covered: continue
            if lower > covered+1e-7: return False
            covered = max(covered, upper)
            if covered >= hi: return True
        return False

    def path(self, start, goal):
        start, goal = tuple(start), tuple(goal)
        if not self.walkable(start) or not self.walkable(goal):
            return None
        if self.clear(start,goal): return [goal]
        # Prefer a safe L when possible; otherwise search the source ground.
        for corner in ((goal[0],start[1]),(start[0],goal[1])):
            if self.clear(start,corner) and self.clear(corner,goal):
                return [p for p in (corner,goal) if p != start]
        low_y=min(r[1] for r in self.ground)
        high_y=max(r[1]+r[3] for r in self.ground)
        xs={12.,self.width-12.,start[0],goal[0]}
        ys={low_y,high_y,start[1],goal[1]}
        xs.update(float(x) for x in range(12,int(self.width-12)+1,12))
        ys.update(float(y) for y in range(math.ceil(low_y),math.floor(high_y)+1,12))
        # Include narrow ground cells and a margin around closed obstacles.
        for x,y,width,height in self.ground:
            xs.update((x,x+width/2,x+width));ys.update((y,y+height/2,y+height))
        for x,y,width,height in self.blocked:
            xs.update((x-8,x+width+8));ys.update((y-8,y+height+8))
        xs=sorted(x for x in xs if 12 <= x <= self.width-12)
        ys=sorted(y for y in ys if low_y <= y <= high_y)
        initial=(bisect.bisect_left(xs,start[0]),bisect.bisect_left(ys,start[1]))
        finish=(bisect.bisect_left(xs,goal[0]),bisect.bisect_left(ys,goal[1]))
        distances={initial:0.};previous={};edges={};valid={}
        def point(node): return xs[node[0]],ys[node[1]]
        def cost(a,b): return abs(a[0]-b[0])+abs(a[1]-b[1])/.65
        pending=[(cost(start,goal),0.,initial)]
        while pending:
            _,distance,node=heapq.heappop(pending)
            if distance != distances.get(node): continue
            if node == finish:
                nodes=[node]
                while node != initial:
                    node=previous[node];nodes.append(node)
                route=[point(n) for n in reversed(nodes)]
                # Keep only turns, so key pulses do not stop at every cell.
                compact=[route[0]]
                for i in range(1,len(route)-1):
                    a,b,c=route[i-1],route[i],route[i+1]
                    if (a[0] == b[0]) != (b[0] == c[0]): compact.append(b)
                compact.append(goal)
                return compact[1:]
            for dx,dy in ((-1,0),(1,0),(0,-1),(0,1)):
                neighbor=(node[0]+dx,node[1]+dy)
                if not (0 <= neighbor[0] < len(xs) and 0 <= neighbor[1] < len(ys)): continue
                if neighbor not in valid: valid[neighbor]=self.walkable(point(neighbor))
                if not valid[neighbor]: continue
                edge=tuple(sorted((node,neighbor)))
                if edge not in edges: edges[edge]=self.clear(point(node),point(neighbor))
                if not edges[edge]: continue
                candidate=distance+cost(point(node),point(neighbor))
                if candidate >= distances.get(neighbor,math.inf): continue
                distances[neighbor]=candidate;previous[neighbor]=node
                heapq.heappush(pending,(candidate+cost(point(neighbor),goal),candidate,neighbor))
        return None


def navigate_pulse(j, goals, context):
    """Plan from the current read-only snapshot, then press one direction key."""
    observed=j.get('navigation')
    if observed is None:
        raise RuntimeError('Runtime omitted read-only navigation rectangles; refusing blind obstacle movement')
    nav=GroundNavigation(observed)
    w=j['world'];start=(w['x'],w['y'])
    route=None;goal=None
    for candidate in goals:
        candidate_route=nav.path(start,candidate)
        if candidate_route:
            route=candidate_route;goal=candidate;break
    if not route:
        raise RuntimeError('No walkable keyboard route: '+str({'context':context,'start':start,'goals':goals}))
    # Replan after every short pulse: monsters move and breakable blockers vanish.
    # A source ground polygon can produce a tiny horizontal waypoint immediately
    # before a vertical turn (for example x=502 -> 504 beside a 505px blocker).
    # That point is geometrically valid for the planner but too close to the
    # runtime collision margin to move into. Skip the micro-segment and execute
    # the following turn directly when it is clear from the current position.
    waypoint_index=next((i for i,p in enumerate(route)
                         if abs(p[0]-start[0])+abs(p[1]-start[1])>.75),0)
    waypoint=route[waypoint_index]
    if waypoint_index+1<len(route):
        next_waypoint=route[waypoint_index+1]
        if (abs(waypoint[0]-start[0])<8 and abs(next_waypoint[1]-waypoint[1])>2 and
            nav.clear(start,(start[0],next_waypoint[1]))):
            waypoint=(start[0],next_waypoint[1])
        elif (abs(waypoint[1]-start[1])<8 and abs(next_waypoint[0]-waypoint[0])>2 and
              nav.clear(start,(next_waypoint[0],start[1]))):
            waypoint=(next_waypoint[0],start[1])
    dx=waypoint[0]-start[0];dy=waypoint[1]-start[1]
    if abs(dx) > .75:
        code=0x27 if dx>0 else 0x25;distance=abs(dx);maximum_speed=300.
    else:
        code=0x28 if dy>0 else 0x26;distance=abs(dy);maximum_speed=195.
    # Repeated arrows may legitimately enter the game's double-tap run. Use its
    # fastest speed to stop before a turn; the following snapshot closes the gap.
    duration=min(.16,max(.018,(distance-.75)/maximum_speed))
    recent=navigation_steps[-8:]
    if len(recent)==8 and all(
        p['context']==context and p['room']==j['room'] and p['key']==code and
        abs(p['start'][0]-start[0])+abs(p['start'][1]-start[1])<.1
        for p in recent):
        raise RuntimeError('Keyboard navigation made no progress for eight pulses: '+str(
            {'context':context,'room':j['room'],'tick':w['tick'],'start':start,
             'goal':goal,'waypoint':waypoint,'key':code,'route':route}))
    navigation_steps.append({'context':context,'room':j['room'],'tick':w['tick'],
                             'start':start,'goal':goal,'route':route,'key':code,'seconds':duration})
    key(code)
    try: time.sleep(duration)
    finally: key(code,False)
    time.sleep(.08)


def position(x,y,tolerance=8):
    original_room=wait(lambda q:True)['room']
    deadline=time.monotonic()+24
    while time.monotonic()<deadline:
        j=wait(lambda q:True); w=j['world']
        if j['room']!=original_room:return
        if w['active']>=0: time.sleep(.1); continue
        dx=x-w['x']; dy=y-w['y']
        if abs(dx)<tolerance and abs(dy)<tolerance: return
        navigate_pulse(j,[(x,y)],'position')
    raise RuntimeError('Could not reach ground position '+str((x,y))+' '+str(state()))


def npc_approach_goal(j, npc):
    """NPC art may stand outside ground. Find a reachable Enter-range point."""
    nav=GroundNavigation(j['navigation']);start=(j['world']['x'],j['world']['y'])
    candidates=[start]
    for dx in range(-120,121,20):
        for dy in range(-120,121,20):
            if abs(dx)+abs(dy)<=140:candidates.append((npc['x']+dx,npc['y']+dy))
    # Ground projections also cover narrow cells between sampling lines.
    for x,y,width,height in nav.ground:
        inset_x=min(8,width/2);inset_y=min(8,height/2)
        candidates.append((min(max(npc['x'],x+inset_x),x+width-inset_x),
                           min(max(npc['y'],y+inset_y),y+height-inset_y)))
    valid=[]
    for point in candidates:
        distance=abs(point[0]-npc['x'])+abs(point[1]-npc['y'])
        if distance>140 or not nav.walkable(point):continue
        # Enter opens the nearest visible NPC, so do not stop at another NPC.
        if any(other['visible'] and other['id']!=npc['id'] and
               abs(point[0]-other['x'])+abs(point[1]-other['y'])<=distance
               for other in j.get('npcs',[])):continue
        valid.append(point)
    for point in sorted(set(valid),key=lambda p:abs(p[0]-start[0])+abs(p[1]-start[1])/.65):
        if nav.path(start,point):return point
    raise RuntimeError('No reachable ordinary interaction point for NPC '+str(npc['id']))


def approach_npc(npc):
    goal=npc_approach_goal(wait(lambda j:True),npc)
    position(*goal,tolerance=5)


def item_quantity(j, item_id):
    return sum(row['count'] for row in j['progression']['inventory'] if row['id']==item_id)


def potion_candidate(j):
    w=j['world'];now=w['tick']*1000/60
    cooldowns=j['progression'].get('cooldowns',{})
    # These are explicit bot thresholds for this demo's 180HP/140MP starter.
    # Observe the game's own cooldown group; never reset it or edit inventory.
    needs=('hp','mp') if w['hp']<=100 else ('mp',)
    for need in needs:
        if need=='mp' and w['mp']>55: continue
        for row in j['progression']['inventory']:
            definition=POTIONS.get(row['id'])
            if definition and definition[need] and cooldowns.get(definition['group'],0)<=now:
                return row['id']
    return None


def use_recovery_if_needed(j):
    item_id=potion_candidate(j)
    if item_id is None: return False
    release();before_count=item_quantity(j,item_id)
    tap('I');wait(lambda q:q.get('panel')==3)
    click(500,129)  # Item inventory, not the avatar tab.
    click(546,295)  # Consumables.
    opened=wait(lambda q:q['region_ui']['bag_tab']==1)
    # This isolated normal run never uses the sort button; item order is the
    # stable inventory order. All recovery items available on this route are
    # the four explicitly identified current-PVF definitions above.
    visible=[row for row in opened['progression']['inventory'] if row['id'] in POTIONS]
    index=next(i for i,row in enumerate(visible) if row['id']==item_id)
    if index>=32: raise RuntimeError('Recovery inventory unexpectedly exceeds one page')
    click(489+30*(index%8),321+30*(index//8),right=True)
    used=wait(lambda q:item_quantity(q,item_id)==before_count-1)
    supply_actions.append({'action':'consume','method':'I / consumables / ordinary right click',
                           'room':j['room'],'tick':j['world']['tick'],'item':item_id,
                           'quantity_before':before_count,'quantity_after':item_quantity(used,item_id),
                           'hp_before':j['world']['hp'],'hp_after':used['world']['hp'],
                           'mp_before':j['world']['mp'],'mp_after':used['world']['mp']})
    tap(0x1b);wait(lambda q:q.get('panel')==0)
    return True


def shortest_room_route(rooms, start, goal):
    """BFS over actual reciprocal L/R/U/D edges, including visited rooms."""
    offsets=((-1,0),(1,0),(0,-1),(0,1));bits=(4,1,2,8);opposite=(1,0,3,2)
    coordinates={(r['x'],r['y']):i for i,r in enumerate(rooms)}
    pending=deque([start]);previous={start:None}
    while pending:
        current=pending.popleft()
        if current==goal:
            route=[]
            while previous[current] is not None:
                parent,direction=previous[current]
                route.append((direction,current));current=parent
            return list(reversed(route))
        room=rooms[current]
        for direction,(dx,dy) in enumerate(offsets):
            if not room['doors']&bits[direction]:continue
            target=coordinates.get((room['x']+dx,room['y']+dy))
            if target is None or target in previous or not rooms[target]['doors']&bits[opposite[direction]]:continue
            previous[target]=(current,direction);pending.append(target)
    raise RuntimeError('Boss is unreachable through reciprocal source doors')


def fight():
    deadline=time.monotonic()+150
    while time.monotonic()<deadline:
        j=wait(lambda q:True); w=j['world']
        assert not any(w['test_mode'].values()), 'Acceptance entered test mode'
        if w['dead']: raise RuntimeError('Player died during normal combat')
        mobs=[m for m in w['monsters'] if not m['dead']]
        if not mobs:return
        if use_recovery_if_needed(j):continue
        if w['active']>=0: time.sleep(.1);continue
        m=min(mobs,key=lambda m:abs(m['x']-w['x'])+2*abs(m['y']-w['y']))
        dx=m['x']-w['x'];dy=m['y']-w['y']
        if w['animation'] in ('attack1','attack2','attack3'):
            # Normal combos have active==-1. Queue X during their actual body
            # animation instead of spending that interval chasing knockback.
            if abs(dx)<100 and abs(dy)<20:tap('X',.025)
            else:time.sleep(.07)
            continue
        if abs(dx)>42 or abs(dy)>6:
            side=1 if dx>=0 else -1
            # Try a normal melee stand point on this side, then the opposite
            # side or target's ground position if an object occupies that spot.
            goals=[(m['x']-side*32,m['y']),(m['x']+side*32,m['y']),(m['x'],m['y'])]
            navigate_pulse(j,goals,'fight-target-'+str(m['id']))
            continue
        if (dx>0)!=(w['direction']>0):tap(0x27 if dx>0 else 0x25,.03)
        # Select an available configured skill; never modify cooldown/MP/state.
        chosen = next((i for i in (8, 1, 0, 6, 9, 11) if
                       w['skills'][i]['cooldown_ms'] == 0 and w['skills'][i]['mp'] <= w['mp']), None)
        if chosen is not None and w['z'] == 0:
            tap('ASDFGHQWERTYU'[w['bindings'].index(chosen)],.035)
        else: tap('X',.035)
        time.sleep(.045)
    raise RuntimeError('Normal combat timeout '+str(state()))


def complete_dungeon(dungeon_id, prefix=''):
    j=wait(lambda q:q['location']=='town')
    minimum={1:1,2:2}[dungeon_id]
    if j['progression']['level']<minimum:
        raise RuntimeError('Ordinary dungeon admission requires level '+str(minimum)+
                           '; actual naturally earned level is '+str(j['progression']['level']))
    trial={'dungeon':dungeon_id,'level_before':j['progression']['level'],
           'xp_before':j['progression']['xp'],'rooms_visited':[],'completed':False}
    dungeon_runs.append(trial)
    move_until(lambda q:q['location']=='entrance',0x27)
    record(prefix+'05-entrance')
    move_until(lambda q:q['select_dungeon'],0x27)
    if dungeon_id==2:
        selection=wait(lambda q:q['select_dungeon'])['dungeon_selection']
        card=next(c for c in selection['cards'] if c['id']==2)
        click(card['x']+card['width']/2,card['y']+card['height']/2)
    enter=wait(lambda q:q['select_dungeon'])['dungeon_selection']['enter_button']
    click(enter['x']+enter['width']/2,enter['y']+enter['height']/2)
    j=wait(lambda q:q['location']=='dungeon' and not q['select_dungeon'])
    assert j['run']['run']['dungeon']==dungeon_id,'UI selected the wrong actual dungeon'
    trial['level_on_entry']=j['progression']['level']
    trial['maze']=j['run']['run']['rooms']
    transitions=0
    while True:
        transitions+=1
        if transitions>4*40:raise RuntimeError('Dungeon traversal exceeded transition budget')
        j=wait(lambda q:q['location']=='dungeon')
        run=j['run']['run'];current=run['current'];rooms=run['rooms'];boss=run['boss']
        assert run['dungeon']==dungeon_id
        trial['rooms_visited'].append(current)
        record(prefix+'06-room-'+str(current))
        fight();record(prefix+'07-cleared-'+str(current))
        j=state()
        if current==boss:break
        direction,target=shortest_room_route(rooms,current,boss)[0]
        gates=j['gates']
        if len(gates)<2*direction+2:raise RuntimeError('MAP omitted required gate '+str(direction))
        x,y=gates[2*direction],gates[2*direction+1]+j['background_y']
        position(x-20 if direction==1 else x+20 if direction==0 else x,
                 y-20 if direction==3 else y+20 if direction==2 else y)
        wait(lambda q:q['room']==target)
    # Clearing and presenting a modal are separate observations. A panel may
    # have been dismissed by an already queued input or concurrent interaction;
    # require the real clear record, then use the visible summary button.
    j=wait(lambda q:any(row['dungeon']==dungeon_id for row in q['progression']['clears'].values()))
    if j.get('panel',0)!=5:
        if j.get('panel',0)!=0:
            raise RuntimeError('Unexpected panel after real boss clear: '+str(j.get('panel')))
        result_panel_actions.append({'dungeon':dungeon_id,'action':'open visible cleared-dungeon summary',
                                     'tick':j['world']['tick'],'panel_before':j.get('panel',0)})
        click(400,105)
    wait(lambda q:q.get('panel',0)==5)
    record(prefix+'07a-boss-results')
    click(260,457);wait(lambda q:q.get('panel',0)==0)
    j=wait(lambda q:any(n['id']==1000 and n['visible'] for n in q.get('npcs',[])))
    merchant=next(n for n in j['npcs'] if n['id']==1000 and n['visible'])
    approach_npc(merchant)
    tap(0x0d);wait(lambda q:q.get('panel',0)==1 and q['region_ui']['npc']==1000)
    record(prefix+'07b-delilah-dialogue')
    click(550,465);wait(lambda q:q.get('panel',0)==2)
    record(prefix+'07c-delilah-shop')
    before=state()['progression'];click(235,465)
    repaired=wait(lambda q:bool(q['region_ui'].get('message')))
    assert repaired['region_ui']['message'].startswith(('修理完成','没有需要修理')),'Unexpected repair result: '+repaired['region_ui']['message']
    assert repaired['progression']['gold']<=before['gold']
    record(prefix+'07d-delilah-repair')
    tap(0x1b);wait(lambda q:q.get('panel',0)==0)
    click(400,105);wait(lambda q:q.get('panel',0)==5)
    click(540,457);j=wait(lambda q:q['location']=='town')
    record(prefix+'08-return-town')
    assert any(row['dungeon']==dungeon_id for row in j['progression']['clears'].values())
    trial.update(completed=True,level_after=j['progression']['level'],xp_after=j['progression']['xp'],
                 hp_after=j['world']['hp'],mp_after=j['world']['mp'],clears=j['progression']['clears'])


def prepare_deep_supplies():
    j=wait(lambda q:q['location']=='town')
    if j['progression']['level']<2:
        raise RuntimeError('Lorien clear did not naturally earn the required level2 for Lorien Inside')
    linus=next(n for n in j['npcs'] if n['id']==1 and n['visible'])
    approach_npc(linus);tap(0x0d)
    wait(lambda q:q['panel']==1 and q['region_ui']['npc']==1)
    click(300,195);click(550,465)
    j=wait(lambda q:q['progression']['quests'].get('102',{}).get('status')=='complete')
    supply_actions.append({'action':'quest-reward','quest':102,'actual_level':j['progression']['level'],
                           'actual_xp':j['progression']['xp'],'gold_after':j['progression']['gold']})
    record('deep-00-lorien-quest-complete')
    click(300,195);click(550,465)
    wait(lambda q:q['progression']['quests'].get('103',{}).get('status')=='active')
    tap(0x1b);tap(0x0d);wait(lambda q:q['panel']==1 and q['region_ui']['npc']==1)
    click(550,465);wait(lambda q:q['panel']==2)
    before=state()
    quantity=min(3,before['progression']['gold']//100)
    if quantity<2:raise RuntimeError('Insufficient normally earned gold for two deep-run MP supplies')
    for _ in range(quantity):
        current=state();click(350,257)  # Source Linus page1 item3: 1112 / 100 gold.
        purchased=wait(lambda q:item_quantity(q,1112)==item_quantity(current,1112)+1)
        assert current['progression']['gold']-purchased['progression']['gold']==100
    supply_actions.append({'action':'purchase','npc':1,'item':1112,'quantity':quantity,'price':100*quantity,
                           'gold_before':before['progression']['gold'],'gold_after':purchased['progression']['gold']})
    if purchased['progression']['gold']>=100:
        current=state();click(350,200)
        purchased=wait(lambda q:item_quantity(q,1106)==item_quantity(current,1106)+1)
        assert current['progression']['gold']-purchased['progression']['gold']==100
        supply_actions.append({'action':'purchase','npc':1,'item':1106,'quantity':1,'price':100,
                               'gold_before':current['progression']['gold'],'gold_after':purchased['progression']['gold']})
    record('deep-01-normal-restock')
    tap(0x1b);wait(lambda q:q.get('panel')==0)


def basic_controls():
    tap('X')
    wait(lambda j:j['world']['animation']=='attack1')
    record('02a-attack1')
    tap('X')
    wait(lambda j:j['world']['animation']=='attack2')
    record('02b-attack2')
    tap('X')
    wait(lambda j:j['world']['animation']=='attack3')
    record('02c-attack3')
    wait(lambda j:j['world']['animation']=='stay')
    start = state()['world']['x']
    tap(0x27,.15)
    moved = wait(lambda j:j['world']['x']>start+10)
    assert moved['world']['active']==-1, 'Normal combo blocked later movement'
    tap('C',.03)
    wait(lambda j:j['world']['z']>0)
    record('02d-jump-after-combo')
    wait(lambda j:j['world']['z']==0 and j['world']['animation']=='stay')
    # Use a fresh pair of key-downs, then keep the second direction held
    # through the dash attack. No state writes or synthetic controller flags.
    tap(0x25,.03)
    key(0x25)
    wait(lambda j:j['world']['animation']=='dash')
    record('02e-double-tap-dash')
    tap('X',.02)
    wait(lambda j:j['world']['animation']=='dashattack')
    record('02f-dash-attack')
    resumed=wait(lambda j:j['world']['animation']=='move')
    assert resumed['world']['pose_frame_override']==-1, 'Movement retained an attack frame override'
    record('02g-held-direction-walk')
    tap('X',.02)
    wait(lambda j:j['world']['animation']=='attack1')
    record('02h-normal-attack-after-dash')
    key(0x25,False)
    wait(lambda j:j['world']['animation']=='stay')
    # Returning to idle must still allow a new, explicit double tap to run.
    tap(0x27,.03)
    key(0x27)
    wait(lambda j:j['world']['animation']=='dash')
    record('02i-fresh-double-tap-dash')
    key(0x27,False)
    wait(lambda j:j['world']['animation']=='stay')


def unlearned_controls():
    click(400,545)
    initial = wait(lambda j:j['screen']==2)
    assert len(initial['world']['skills'])==13 and all(s['level']==0 for s in initial['world']['skills'])
    assert not any(initial['world']['test_mode'].values())
    record('zero-01-loaded')
    tap('K');wait(lambda j:j['skill_menu'])
    record('zero-02-skill-levels')
    tap(0x1b);wait(lambda j:not j['skill_menu'])
    mp = state()['world']['mp']
    observations = []

    def rejected(label, code):
        tap(code,.02)
        world = wait(lambda j:True)['world']
        assert world['active']==-1 and world['mp']==mp and world['effects']==0, label
        assert all(s['level']==0 and s['cooldown_ms']==0 for s in world['skills']), label
        observations.append({'case':label,'world':world})

    for code in 'ASDFGHQWERTY': rejected('ground-'+code,code)
    rejected('ground-Space',0x20)
    tap('C',.02);wait(lambda j:j['world']['z']>0)
    rejected('air-G', 'G')
    rejected('air-H', 'H')
    wait(lambda j:j['world']['z']==0 and j['world']['animation']=='stay')
    tap(0x27,.03);key(0x27)
    wait(lambda j:j['world']['animation']=='dash')
    tap('X',.02)
    # The core paired control uses the actual source ANI start of frame3;
    # do not let an early-frame denial masquerade as a learned-level check.
    core = json.loads((root/'reports/combat-native-reverse/skill-eligibility-tests.json').read_text(encoding='utf-8'))
    assert core['status']=='pass'
    dash_case = next(case for case in core['zero_level_cases'] if case['skill_id']==11)
    frame3_ms = -dash_case['before']['anim_start']
    assert frame3_ms > 0 and dash_case['after_learned']['active_skill']==3
    wait(lambda j:j['world']['animation']=='dashattack' and j['world']['player_animation_ms']>=frame3_ms)
    rejected('dash-followup-F','F')
    key(0x27,False)
    wait(lambda j:j['world']['animation']=='stay')
    record('zero-03-rejected-shortcuts')
    tap('X',.02);wait(lambda j:j['world']['animation']=='attack1')
    record('zero-04-ordinary-attack')
    wait(lambda j:j['world']['animation']=='stay')
    start = state()['world']['x']
    tap(0x25,.15)
    wait(lambda j:j['world']['x']<start-10)
    record('zero-05-movement')
    u.PostMessageW(window,0x10,0,0)
    assert process.wait(timeout=15)==0
    events = json.loads((report/'events.json').read_text(encoding='utf-8'))
    assert not any(e['kind']=='stage' for e in events), 'An unlearned skill committed a stage between observations'
    disk = json.loads((saves/'characters.json').read_text(encoding='utf-8'))
    assert all(value==0 for value in disk['characters'][0]['skills'].values())
    launch('reload');wait(lambda j:j['screen']==0,suffix='reload')
    click(400,545)
    restored = wait(lambda j:j['screen']==2,suffix='reload')
    assert all(s['level']==0 for s in restored['world']['skills'])
    assert restored['world']['mp']==mp and not any(restored['world']['test_mode'].values())
    record('zero-06-reloaded',suffix='reload')
    (report/'unlearned-check.json').write_text(json.dumps({
        'status':'pass','binary_sha256':binary_sha256,'observations':observations,
        'stage_event_count':0,'dash_source_frame3_ms':frame3_ms,'all_13_levels_zero_after_process_reload':True,
        'scope':'Isolated core save fixture, visible SDL window messages, ground/air/dash shortcut rejection, ordinary attack/movement and actual process reload; not native timing or full qualification parity'},indent=2),encoding='utf-8')


def settings_controls():
    tap(0x1b);click(190,150)
    initial=wait(lambda j:j.get('settings_menu') and j.get('menu'))
    assert initial['requested_balance']['normal_hp_multiplier']==2
    assert initial['requested_balance']['boss_hp_multiplier']==3
    record('settings-01-defaults')
    # Each bus is changed by its own ordinary button, including the master.
    for y in (140,185,230,275): click(535,y+16)
    changed=wait(lambda j:all(abs(j['settings']['audio'][k]-.9)<1e-6 for k in ('master','music','effects','ambient')))
    click(595,336);click(595,381)
    expected=wait(lambda j:j['requested_balance']['normal_hp_multiplier']==3 and j['requested_balance']['boss_hp_multiplier']==4)
    assert all(abs(expected['audio']['volumes'][k]-v)<1e-6 for k,v in expected['settings']['audio'].items())
    assert expected['world']['test_mode']==initial['world']['test_mode']
    record('settings-02-changed')
    u.PostMessageW(window,0x10,0,0);assert process.wait(timeout=15)==0
    disk=json.loads((saves/'settings.json').read_text(encoding='utf-8'))
    assert disk['audio']==expected['settings']['audio']
    assert disk['demo_balance']==expected['requested_balance']
    launch('reload');wait(lambda j:j['screen']==0,suffix='reload')
    click(400,545);wait(lambda j:j['screen']==2,suffix='reload')
    tap(0x1b);click(190,150)
    restored=wait(lambda j:j.get('settings_menu'),suffix='reload')
    assert restored['settings']==disk
    assert restored['requested_balance']==expected['requested_balance']
    assert restored['audio']['volumes']==expected['audio']['volumes']
    record('settings-03-reloaded','reload')
    (report/'settings-check.json').write_text(json.dumps({
        'status':'pass','defaults':initial['requested_balance'],
        'persisted':disk,'reloaded_audio':restored['audio'],
        'scope':'Ordinary settings UI, independent bus controls, save and process reload; PCM is not listening verification',
        'binary_sha256':binary_sha256},indent=2),encoding='utf-8')


def gorecross_controls():
    """Observe both directions through the real R shortcut, with no clock writes."""
    trials=[]
    for code,direction,label in ((0x25,-1,'left'),(0x27,1,'right')):
        wait(lambda j:j['world']['active']==-1 and j['world']['z']==0
             and j['world']['skills'][9]['cooldown_ms']==0)
        tap(code,.02)
        wait(lambda j:j['world']['animation']=='stay' and j['world']['direction']==direction)
        before=state()['world']
        tap('R',.02)
        started=wait(lambda j:j['world']['active']==9)
        assert started['world']['mp']==before['mp']-before['skills'][9]['mp']
        # Holding a direction during the skill exercises the frame10 unlock;
        # it must not turn the first two slashes into an idle/move cancellation.
        key(code)
        samples=[];captured=set();deadline=time.monotonic()+4
        last_tick=-1
        while time.monotonic()<deadline:
            observed=state()
            if not observed: time.sleep(.01);continue
            w=observed['world']
            if w['tick']==last_tick: time.sleep(.01);continue
            last_tick=w['tick']
            samples.append(w)
            phase=w['gorecross']['phase']
            has_blood=any(e['phase']=='gorecross:projectile' for e in w['effect_instances'])
            stage=('released' if w['active']==-1 and has_blood else 'attached' if phase==0
                   else 'second-slash' if phase==1 else 'blood-cross' if phase==3 else None)
            if stage and stage not in captured:
                captured.add(stage)
                path=report/'manual.png'
                previous=path.stat().st_mtime_ns if path.exists() else 0
                key(0x7b);key(0x7b,False)
                capture_deadline=time.monotonic()+1
                while time.monotonic()<capture_deadline:
                    if path.exists() and path.stat().st_mtime_ns>previous:
                        target=report/('gorecross-'+label+'-'+stage+'.png')
                        target.write_bytes(path.read_bytes())
                        break
                    time.sleep(.01)
                else: raise RuntimeError('Missing ordinary skill framebuffer capture')
            if w['active']==-1: break
        else: raise RuntimeError('GoreCross failed to release actor')
        key(code,False)
        wait(lambda j:j['world']['animation']=='stay')
        trials.append({'direction':label,'samples':samples,'captures':sorted(captured)})
        (report/'gorecross-observations.json').write_text(json.dumps(trials,indent=2),encoding='utf-8')
        active=[w for w in samples if w['active']==9]
        assert all(w['x']==started['world']['x'] for w in active), 'Held direction moved actor before release'
        assert all(w['direction']==direction for w in active)
        assert {'attached','second-slash','blood-cross','released'}<=captured, 'Missing observed GoreCross stage: '+str(captured)
        assert any(sum(e['phase'].startswith('gorecross:attached-') for e in w['effect_instances'])==4 for w in active), 'Four separate source attachments were not observed'
        assert any(w['gorecross']['phase']==1 and not any(e['phase']=='gorecross:projectile' for e in w['effect_instances']) for w in active), 'Blood cross appeared before the independent layer event'
        assert any(w['active']==-1 and any(e['phase']=='gorecross:projectile' for e in w['effect_instances']) for w in samples), 'Independent blood cross did not survive body release'
        assert all(not(e['skill']==64 and e['phase'].startswith('gorecross:attached-'))
                   for e in samples[-1]['effect_instances']), 'Body attachments survived state exit'
        print('gorecross-'+label, 'ordinary shortcut, four layers, projectile and release observed',flush=True)
    (report/'gorecross-check.json').write_text(json.dumps({
        'status':'pass','binary_sha256':binary_sha256,'trials':trials,
        'scope':'Ordinary R shortcut with held direction; source-layer/event/release observation, not target collision or original-PC visual parity'
    },indent=2),encoding='utf-8')

try:
    launch()
    wait(lambda j:j['screen']==0)
    if args.unlearned_fixture:
        unlearned_controls()
        raise UiReviewComplete()
    if args.appearance_fixture:
        record('00-selection-outfit')
        click(400,545);wait(lambda j:j['screen']==2)
        record('01-world-outfit')
        tap('I');wait(lambda j:j['panel']==3)
        record('02-weapon-tooltip',hover=(660,155))
        click(575,129);record('03-worn-avatar')
        click(655,214,right=True);wait(lambda j:'[coat avatar]' not in j['progression']['equipped'])
        record('04-coat-removed')
        click(524,342,right=True)
        j=wait(lambda j:j['progression']['equipped'].get('[coat avatar]')==4)
        expected=j['progression'];record('05-coat-replaced')
        tap(0x1b);wait(lambda j:j['panel']==0)
        key(0x27);wait(lambda j:j['world']['animation']=='move');record('06-move-right');key(0x27,False)
        key(0x25);wait(lambda j:j['world']['animation']=='move' and j['world']['direction']<0);record('07-move-left');key(0x25,False)
        tap('X');wait(lambda j:j['world']['animation']=='attack1');record('08-attack-left')
        wait(lambda j:j['world']['animation']=='stay')
        tap(0x27,.03);tap('X');wait(lambda j:j['world']['animation']=='attack1');record('09-attack-right')
        wait(lambda j:j['world']['animation']=='stay')
        tap(0x0d);wait(lambda j:j['panel']==1)
        click(550,465);wait(lambda j:j['panel']==2)
        click(550,465);wait(lambda j:j['panel']==3)
        click(500,129)
        click(485,317,right=True)
        j=wait(lambda j:all(x['id']!=27118 for x in j['progression']['inventory']))
        expected=j['progression'];record('09a-vendor-sale')
        tap(0x1b);wait(lambda j:j['panel']==0)
        u.PostMessageW(window,0x10,0,0);assert process.wait(timeout=15)==0
        launch('reload');wait(lambda j:j['screen']==0,suffix='reload')
        record('10-selection-reload',suffix='reload')
        click(400,545);j=wait(lambda j:j['screen']==2,suffix='reload')
        assert j['progression']['equipped']==expected['equipped']
        assert j['progression']['inventory']==expected['inventory']
        assert j['progression']['future_appearance_rules']==expected['future_appearance_rules']
        tap('I');wait(lambda j:j['panel']==3,suffix='reload');click(575,129)
        record('11-avatar-reload',suffix='reload')
        raise UiReviewComplete()
    click(200,550);wait(lambda j:j['screen']==1)
    for ch in 'Native17': tap(ch,.03)
    record('01-create')
    click(400,575);wait(lambda j:j['screen']==0)
    click(400,545);wait(lambda j:j['screen']==2)
    record('02-room')
    if args.settings_only:
        settings_controls()
        raise UiReviewComplete()
    if args.ui_only:
        tap('I');wait(lambda j:j['panel']==3)
        record('03-inventory')
        record('04-item-details',hover=(660,155))
        click(660,155,right=True);wait(lambda j:'[weapon]' not in j['progression']['equipped'])
        record('04a-unequipped')
        click(485,317,right=True);wait(lambda j:'[weapon]' in j['progression']['equipped'])
        record('04b-equipped')
        baseline=wait(lambda j:True)['progression']
        click(575,129);record('04c-avatar')
        click(680,314);wait(lambda j:j['region_ui']['fitting'])
        click(524,342);click(553,342)
        wait(lambda j:len(j['region_ui']['fitting_items'])==2)
        record('04d-fitting')
        assert wait(lambda j:True)['progression']==baseline, 'Fitting altered persistent equipment/inventory'
        click(590,289);wait(lambda j:not j['region_ui']['fitting_items'])
        record('04e-fitting-reset')
        tap(0x1b);wait(lambda j:j['panel']==0)
        tap(0x0d);wait(lambda j:j['panel']==1)
        record('05-npc-dialogue')
        click(300,195);record('06-quest-description')
        click(550,465);wait(lambda j:bool(j['progression']['quests']))
        tap(0x1b);wait(lambda j:j['panel']==0)
        tap('L');wait(lambda j:j['panel']==4)
        record('07-quest-list')
        raise UiReviewComplete()
    basic_controls()
    if args.controls_only:
        gorecross_controls()
        raise UiReviewComplete()
    tap('K');wait(lambda j:j['skill_menu'])
    click(190,138) # Upper Slash Lv2
    click(190,167) # Swap A/S binding
    # Exercise the existing demo skill configuration through its visible controls.
    # Keep the previously disclosed demo skill levels. This is not a Lv1 balance
    # acceptance; normal quest supplies below are acquired through visible UI.
    for _ in range(7): click(390,138)  # Ghost Slash Lv8
    for _ in range(7): click(190,268)  # Wave Lv8
    for _ in range(4): click(570,268)  # Vane Slash Lv5
    tap(0x1b)
    record('03-configured')
    tap(0x0d);wait(lambda j:j['panel']==1 and j['region_ui']['npc']==2)
    # Available Seria rows are 101 then 1016. Accept and immediately turn in
    # the source meet-Seria quest; the source rewards supply HP/MP recovery.
    click(300,230);click(550,465)
    wait(lambda j:j['progression']['quests'].get('1016',{}).get('status')=='active')
    click(550,465)
    j=wait(lambda j:j['progression']['quests'].get('1016',{}).get('status')=='complete')
    assert item_quantity(j,1055)>=3 and item_quantity(j,1004)>=3
    supply_actions.append({'action':'quest-reward','quest':1016,'hp_item':1055,'hp_quantity':item_quantity(j,1055),
                           'mp_item':1004,'mp_quantity':item_quantity(j,1004)})
    record('03a-normal-quest-supplies')
    click(300,195);click(550,465)
    wait(lambda j:j['progression']['quests'].get('101',{}).get('status')=='active')
    tap(0x1b);wait(lambda j:j['panel']==0)
    move_until(lambda j:j['location']=='town',0x28)
    record('04-town')
    j=state();linus=next(n for n in j['npcs'] if n['id']==1 and n['visible'])
    approach_npc(linus)
    tap(0x0d);wait(lambda j:j['panel']==1 and j['region_ui']['npc']==1)
    click(300,195);click(550,465)
    wait(lambda j:j['progression']['quests'].get('101',{}).get('status')=='complete')
    # Continue the normal Lorien clear quest, then reopen a clean shop panel.
    click(300,195);click(550,465)
    wait(lambda j:j['progression']['quests'].get('102',{}).get('status')=='active')
    tap(0x1b);tap(0x0d);wait(lambda j:j['panel']==1 and j['region_ui']['npc']==1)
    click(550,465);wait(lambda j:j['panel']==2)
    before=state();click(350,200)  # Linus page1 item1: source 1106, 100 gold.
    purchased=wait(lambda j:item_quantity(j,1106)==item_quantity(before,1106)+1)
    assert before['progression']['gold']-purchased['progression']['gold']==100
    supply_actions.append({'action':'purchase','npc':1,'item':1106,'quantity':1,'price':100,
                           'gold_before':before['progression']['gold'],'gold_after':purchased['progression']['gold']})
    record('04a-normal-shop-supply')
    tap(0x1b);wait(lambda j:j['panel']==0)
    complete_dungeon(1)
    if args.deep:
        prepare_deep_supplies()
        complete_dungeon(2,'deep-')
    tap(0x1b);click(400,405);wait(lambda j:j['screen']==0)
    saved=json.loads((saves/'characters.json').read_text(encoding='utf-8'))
    assert saved['characters'][0]['skills']['46']==2
    assert saved['characters'][0]['bindings'][0]==5
    u.PostMessageW(window,0x10,0,0);assert process.wait(timeout=15)==0
    launch('reload')
    wait(lambda j:j['screen']==0,suffix='reload')
    click(400,545);wait(lambda j:j['screen']==2,suffix='reload')
    record('09-reloaded','reload')
    configured = next(x['state']['world'] for x in steps if x['name']=='03-configured')
    reloaded = steps[-1]['state']['world']
    assert [x['level'] for x in configured['skills']] == [x['level'] for x in reloaded['skills']]
    assert configured['bindings'] == reloaded['bindings']
    expected_dungeons={1,2} if args.deep else {1}
    cleared_on_reload={row['dungeon'] for row in steps[-1]['state']['progression']['clears'].values()}
    assert expected_dungeons<=cleared_on_reload,'Reload lost actual dungeon clear records'
    (report/'reload-check.json').write_text(json.dumps({
        'scope':'Actual configured and reloaded runtime snapshots through normal window input',
        'binary_sha256':binary_sha256,
        'configured_skills':configured['skills'], 'reloaded_skills':reloaded['skills'],
        'configured_bindings':configured['bindings'], 'reloaded_bindings':reloaded['bindings'],
        'levels_equal':True, 'bindings_equal':True,
        'dungeons_cleared_on_reload':sorted(cleared_on_reload),
        'actual_character_level_on_reload':steps[-1]['state']['progression']['level'],
        'test_mode_off_at_recorded_steps':all(not any(x['state']['world']['test_mode'].values()) for x in steps)
    },indent=2),encoding='utf-8')
    u.PostMessageW(window,0x10,0,0);assert process.wait(timeout=15)==0
    after=json.loads((saves/'characters.json').read_text(encoding='utf-8'))
    assert after['characters'][0]['skills']==saved['characters'][0]['skills']
    assert after['characters'][0]['bindings']==saved['characters'][0]['bindings']
    result={'status':'pass','input':('SendInput scan-code keyboard; window mouse messages; English game-thread layout; IME excluded' if args.physical_keys else 'Windows window keyboard/mouse messages through SDL; ordinary mode; live state observed only'),
            'steps':len(steps),'reload_runtime_configuration_equal':True,
            'configured_skill_levels':{x['id']:x['level'] for x in configured['skills']}}
except UiReviewComplete:
    result={'status':'pass','input':('Windows window keyboard/mouse messages through SDL; isolated core zero-level skill fixture' if args.unlearned_fixture else 'Windows window keyboard/mouse messages through SDL; isolated core appearance fixture' if args.appearance_fixture else 'Windows window keyboard/mouse messages through SDL; isolated new character'),
            'scope':('Core-generated zero-level fixture; rejection, ordinary movement/attack and process reload; full native qualification and physical keys remain unverified' if args.unlearned_fixture else 'Ordinary volume/HP settings UI and actual process reload; no original-client UI parity claim' if args.settings_only else 'Ordinary combo, jump, double-tap dash, dash attack and held-direction return to normal attack; no original-client timing parity claim' if args.controls_only else 'Core-generated isolated appearance fixture; UI equipment changes/world pose captures/reload, not gameplay acquisition' if args.appearance_fixture else 'UI navigation and actual framebuffer captures only; visual review and PC pixel parity remain separate'),
            'steps':len(steps)}
except Exception as error:
    result={'status':'fail','error':str(error),'traceback':traceback.format_exc()}
finally:
    try: release()
    except Exception as cleanup_error:
        result['input_cleanup_error']=str(cleanup_error)
        result['status']='fail'
    if process and process.poll() is None:
        u.PostMessageW(window,0x10,0,0)
        try:process.wait(timeout=15)
        except subprocess.TimeoutExpired:process.terminate();process.wait()
    u.SetCursorPos(original_cursor.x,original_cursor.y)
    after_user={p.name:hashlib.sha256(p.read_bytes()).hexdigest() for p in (root/'saves').glob('*') if p.is_file()}
    (report/'user-save-hashes-after.json').write_text(json.dumps(after_user,indent=2),encoding='utf-8')
    result['user_saves_unchanged']=user_saves==after_user
    result['changed_user_save_files']=sorted(k for k in user_saves.keys()|after_user.keys() if user_saves.get(k)!=after_user.get(k))
    result['report_directory']=str(report.relative_to(root))
    result['binary_sha256']=binary_sha256
    result['navigation_pulses']=len(navigation_steps)
    (report/'navigation-steps.json').write_text(json.dumps(navigation_steps,indent=2),encoding='utf-8')
    result['supply_actions']=supply_actions
    result['requested_dungeons']=([1,2] if args.deep else [1]) if not (args.ui_only or args.appearance_fixture or args.settings_only or args.controls_only or args.unlearned_fixture) else []
    result['dungeon_runs']=dungeon_runs
    result['result_panel_actions']=result_panel_actions
    (report/'dungeon-runs.json').write_text(json.dumps(dungeon_runs,indent=2),encoding='utf-8')
    result['combat_bot_policy']={'room_route':'BFS to boss using reciprocal source doors; optional branches excluded',
        'recovery':'normal Seria quest 1016 rewards and one 100-gold Linus HP purchase; I / consumables / right click',
        'hp_threshold':100,'mp_threshold':55,'skill_configuration':'Upper2, Ghost8, Wave8, Vane5; other basic skills1',
        'cheats':False,'process_limit_seconds':900,'room_combat_limit_seconds':150}
    (report/'supply-actions.json').write_text(json.dumps(supply_actions,indent=2),encoding='utf-8')
    (report/'acceptance.json').write_text(json.dumps(result,indent=2),encoding='utf-8')
    print(json.dumps(result,indent=2),flush=True)
raise SystemExit(0 if result['status']=='pass' else 1)

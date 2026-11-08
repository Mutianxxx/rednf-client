# -*- coding: utf-8 -*-
"""T1b 逐行精修批量生成器（终版）—— 语义层 + 客观形态层
语义层（优先）：调用名 / 虚表槽 / 字段名 / 全局变量 / 字符串模板 / new
客观形态层（兜底）：赋值 / 返回 / 自增 / 结构关键字 / case / label（只描述行为，零猜测）
规范：文本禁半角引号与 /* */；非注释行零改动；不产生以 // 0x 起头的注释
"""
import io, os, re, json, sys, glob

ROOT = r"E:\DOF LX\【40JP逆向源代码工程】"

NM = json.load(io.open(os.path.join(ROOT, "work/_t1_namemap.json"), encoding="utf-8"))
COREF = {}
try:
    COREF = {int(k): v for k, v in json.load(io.open(os.path.join(ROOT, "work/_t1b_corefields.json"), encoding="utf-8")).items()}
except Exception:
    pass
ALLF = {}
try:
    ALLF = {int(k): v for k, v in json.load(io.open(os.path.join(ROOT, "work/_t1b_allfields.json"), encoding="utf-8")).items()}
except Exception:
    pass
OFFM = {}
for k, v in (json.load(io.open(os.path.join(ROOT, "work/t1_offmap.json"), encoding="utf-8")) or {}).items():
    try:
        if len(v) > 1 and int(v[1]) >= 150:
            OFFM[int(k, 16)] = v[0]
    except Exception:
        pass

CFIELDS, _FR = {}, re.compile(r'^\s*(?:unsigned char|uint8_t|uint16_t|uint32_t|uint64_t|unsigned int|int|float|double|char|void)\s+(\w+)\s*;\s*//\s*\+0x([0-9A-Fa-f]+)\s*\((\d+)\)')
for p in glob.glob(os.path.join(ROOT, "include/arad/_fields/*.h")):
    cls = os.path.splitext(os.path.basename(p))[0]
    d = {}
    for l in io.open(p, encoding="utf-8", errors="replace"):
        m = _FR.match(l)
        if m and not m.group(1).startswith("_") and not m.group(1).startswith("unused"):
            d[int(m.group(3))] = m.group(1)
    if d:
        CFIELDS[cls] = d

PKT = json.load(io.open(os.path.join(ROOT, "work/_t1_pkt.json"), encoding="utf-8"))
SLOTMAP = {}
try:
    SLOTMAP = json.load(io.open(os.path.join(ROOT, "work/_t1b_slotmap.json"), encoding="utf-8"))
except Exception:
    pass

GLOB = {
 "dword_8F7C04": "本地玩家对象", "dword_8F7C08": "副玩家/观战对象",
 "dword_8F8520": "会话/UDP 管理器", "dword_8F8528": "主管理器(消息/弹窗)",
 "dword_8F8500": "对象链表头", "dword_8F7B08": "网络连接对象",
 "dword_8F7A24": "登录/选区管理器", "dword_8F7C0C": "现金(Cash)",
 "word_8F7C10": "疲劳值", "word_8F7C14": "疲劳上限",
 "word_77F804": "本机身份键(ServerId)", "dword_8F84F0": "地图/区域表",
 "dword_8F850C": "房间/席位表", "dword_8F8524": "登录管理器",
 "dword_8F852C": "角色/物品栏管理器", "dword_8F8548": "用户震动强度档",
 "dword_8F8544": "镜头特写开关", "dword_79C0B0": "默认字体/绘制资源",
 "dword_9B7C48": "PO 定义索引表", "dword_8F84C8": "PO 定义档案管理器",
 "dword_79D100": "16 条时间域累计 tick", "dword_79D0C0": "16 条时间域速率",
 "dword_8F8538": "随身影身/占位管理器", "dword_8F8540": "物品栏刷新器",
 "unk_98BA60": "HTTP 目标 URL", "dword_99FB68": "HTTP XOR 密钥",
 "dword_9D21E0": "WSAStartup 初始化标志",
}
VT = {
 40: "条件位掩码测试(273受击/529濒死/17有血/65机械)",
 116: "取伤害数值", 120: "动画对象", 200: "取动画对象",
 204: "定时器插入", 208: "定时器移除", 212: "播放音效 TAG(→50 声道)",
 228: "主状态写入(0自由/1硬直/2冻结)",
 304: "是否本地玩家", 308: "是否本地玩家", 312: "濒死/一击表现(LAST STRIKE)",
 344: "取坐标三元组", 348: "取坐标对象", 476: "本地扫掠(客户端本地碰撞)",
 512: "命中主处理器(受击方总入口)", 560: "受击反应 setState(3硬直/4击退/5击倒)",
 600: "无敌门", 608: "无敌门", 628: "伤害流水线九步", 672: "自身 HP",
 684: "取攻击上下文", 692: "飘字参数回写", 720: "霸体(HA)开关",
 728: "HP setter/扣血", 760: "状态槽写入(17 槽异常状态)", 776: "异常状态查询",
}
UNIV = {6556: "大状态ID", 7252: "当前目标", 7148: "大状态镜像槽", 7112: "影身开关",
 7096: "影身窗口起始", 7100: "影身窗口时长", 7808: "风格/分支选择",
 6228: "17 槽异常状态数组", 6468: "18 观察者槽", 6132: "属性块",
 6716: "出生音效名", 6740: "冻结标志"}

# 零信息注释（T1 铁律禁止）：纯寄存器名/自增自减/纯结构重复
BAN = re.compile(r'^(?:[a-z_]\w*\s*自增|[a-z_]\w*\s*自减|[a-z_]\w*\s*前进 \d+)$|'
                 r'^(?:eax|ebx|ecx|edx|esi|edi|esp|ebp|st7|al|bl|cl|dl|zf|ax|dx|ah|bh|ch|dh|rax|rbx|开始|结束|返回)$')

def loop_ann(text):
    """循环语句头 —— 抽出循环变量/边界，给出实质描述"""
    text = re.sub(r'\s*\{\s*$', '', text).strip()
    text = re.sub(r'\s+\)', ')', text)
    text = re.sub(r'\{$', '', text).strip()
    t = re.sub(r'^for \(\s*(?:int|unsigned|signed|long|short|uint\w+|char|size_t|DWORD|WORD|BYTE|__int64)\s+', 'for ( ', text)
    t = re.sub(r'^for \(\s*', 'for ( ', t)
    t = re.sub(r'\s*\)$', ')', t)
    tm = re.match(r'^for \( (\w+) = (\w+); \1 != (\d+); --\1\)$', t)
    if tm:
        return "循环：%s 从 %s 递减到 %s" % (tm.group(1), tm.group(2), tm.group(3))
    tm = re.match(r'^for \( (\w+) = (\d+); \1 != (\d+); \+\+\1\)$', t)
    if tm:
        return "循环：%s 从 %s 递增到 %s" % (tm.group(1), tm.group(2), tm.group(3))
    tm = re.match(r'^for \( (\w+) = (\d+); \1 < (\d+); \+\+\1\)$', t)
    if tm:
        return "循环：%s 从 %s 递增到 %s" % (tm.group(1), tm.group(2), tm.group(3))
    tm = re.match(r'^for \( (\w+) = (\w+); \1 != (\w+); \+\+\1\)$', t)
    if tm:
        return "循环：%s 从 %s 递增到 %s" % (tm.group(1), tm.group(2), tm.group(3))
    tm = re.match(r'^for \( (\w+) = (\w+); \1 != (\w+); --\1\)$', t)
    if tm:
        return "循环：%s 从 %s 递减到 %s" % (tm.group(1), tm.group(2), tm.group(3))
    tm = re.match(r'^for \( (\w+) = (\w+); ; \+\+\1\)$', text)
    if tm:
        return "无限循环：%s 从 %s 递增" % (tm.group(1), tm.group(2))
    tm = re.match(r'^for \( (\w+) = 1; (\w+) != 0; --\1\)$', text)
    if tm:
        return "循环：%s 递减到 0" % tm.group(1)
    if re.match(r'^for \(', text):
        return "遍历循环"
    m = re.match(r'^while \( 1 \)$', text)
    if m:
        return "无限循环"
    m = re.match(r'^while \( (\w+) \)$', text)
    if m:
        return "当 %s 非 0 循环" % m.group(1)
    m = re.match(r'^while \( (\w+) != (.+) \)$', text)
    if m:
        return "当 %s != %s 循环" % (m.group(1), short(m.group(2), 24))
    m = re.match(r'^while \( (\w+) < (.+) \)$', text)
    if m:
        return "当 %s < %s 循环" % (m.group(1), short(m.group(2), 24))
    if re.match(r'^while \(', text):
        return "条件循环"
    if text == "do":
        return "do-while 循环体起点"
    return None

def clean(v):
    v = re.sub(r'^[★☆\s]+', '', v.strip())
    v = re.sub(r'\[[^\]]*\]', '', v)
    v = v.split("——")[-1].strip()
    v = v.replace("【", "(").replace("】", ")")
    return v.replace('"', '').replace("'", "").replace("/*", "").replace("*/", "")

def short(s, n=78):
    return s if len(s) <= n else s[:n] + "…"

FLOATBITS = {1065353216: "1.0f", 1056964608: "0.5f", 1073741824: "2.0f",
             1069547520: "1.5f", 1082130432: "4.0f", 1120403456: "100.0f",
             1123024896: "120.0f", 1092616192: "10.0f", 1084227584: "5.0f",
             1097859072: "15.0f", 1101004800: "20.0f", 1112014848: "50.0f",
             1061158912: "0.75f", 1090519040: "8.0f"}

def const_hint(v):
    v = v.strip()
    try:
        n = int(v)
    except Exception:
        return v
    if n in FLOATBITS:
        return FLOATBITS[n]
    return v

def nm_ann(vh):
    v = NM.get("0x" + vh.lower())
    return clean(v) if isinstance(v, str) else None

def funcdef_ann(text, va=None):
    """函数定义行 —— 优先用本块 VA 的精确语义（避免跨类槽位误归属）"""
    if va is not None:
        a = nm_ann(va)
        if a:
            # 若语义名只是 类名__vmtXX（纯符号重复），无信息量 → 跳过
            if re.match(r'^[\w:]+__vmt[0-9A-Fa-f]+$', a) or a == text.split('(')[0].split()[-1]:
                return None
            return "实现：%s" % short(a, 70)
        return None
    m = re.search(r'\bsub_([0-9A-F]{6})\b', text)
    if m:
        a = nm_ann(m.group(1))
        if a:
            return "函数 %s：%s" % (m.group(0), short(a, 60))
    return None

def classify_needs_funcdef():
    return None

def field_name(off, cls):
    if cls in CFIELDS and off in CFIELDS[cls]:
        return CFIELDS[cls][off]
    if off in COREF:
        return COREF[off]
    if off in UNIV:
        return UNIV[off]
    if off in ALLF:
        return ALLF[off]
    return OFFM.get(off)

def byte_off_of(text):
    m = re.search(r'\*\((\w+) \*\)\(this \+ (\d+)\)', text)
    if m:
        return int(m.group(2))
    TYPSZ = {"uint8_t": 1, "int8_t": 1, "char": 1, "uint16_t": 2, "int16_t": 2,
             "uint32_t": 4, "int32_t": 4, "int": 4, "float": 4,
             "uint64_t": 8, "int64_t": 8, "double": 8}
    m = re.search(r'\*\(\(\s*(\w+)\s*\*\)this \+ (\d+)\)', text)
    if m:
        return int(m.group(2)) * TYPSZ.get(m.group(1), 4)
    m = re.search(r'\*\(this \+ (\d+)\)', text)
    if m:
        return int(m.group(1)) * 4
    m = re.search(r'this \+ (\d+)', text)
    if m:
        return int(m.group(1))
    return None

WRITE_R = re.compile(r'^\*(?P<cast>\([^()]*\))?\s*\(?(?P<body>.+?)\)?\s*=\s*(?P<val>.+);$')
PTR_THIS = [
    (re.compile(r'^\(\s*uint(?:8|16|32|64)_t\s*\*\s*\)\s*this\s*\+\s*(\d+)$'), 4),
    (re.compile(r'^\(\s*uint(?:8|16|32|64)_t\s*\*\s*\)\s*\(\s*this\s*\+\s*(\d+)\s*\)$'), 1),
    (re.compile(r'^\(\s*uint(?:8|16|32|64)_t\s*\*\s*\)\s*\(\s*this\s*\+\s*(\d+)\s*\)\s*$'), 1),
    (re.compile(r'^this\s*\+\s*(\d+)$'), 4),
]
def ptr_off(body, base, mult):
    """扩展: 匹配 (*base + N) / (*base + N*4) 等形式"""
    return None

def field_write(text, cls):
    """字段写入：*(uint32_t *)(this + N) = V;  / *((uint8_t *)this + N) = V; / *(this + N) = V;"""
    t = text
    if not t.startswith("*") or not t.endswith(";"):
        return None
    inner = t[1:-1]                 # 去掉前导 * 与结尾 ;
    # 拆 = 号（右侧）
    eq = None
    depth = 0
    for k, ch in enumerate(inner):
        if ch in "([":
            depth += 1
        elif ch in ")]":
            depth -= 1
        elif ch == "=" and depth == 0 and not (k and inner[k-1] in "=!<>+-*/%&|^"):
            if k + 1 < len(inner) and inner[k+1] == "=":
                continue
            eq = k
            break
    if eq is None:
        return None
    lhs, val = inner[:eq].strip(), inner[eq+1:].strip()
    # 去一层平衡外括号: "((uint32_t *)this + 1)" -> "(uint32_t *)this + 1"
    if lhs.startswith("(") and lhs.endswith(")"):
        d = 0
        balanced = True
        for k, ch in enumerate(lhs):
            if ch == "(":
                d += 1
            elif ch == ")":
                d -= 1
                if d == 0 and k != len(lhs) - 1:
                    balanced = False
                    break
        if balanced:
            lhs = lhs[1:-1].strip()
    off = None
    TYPSZ = {"uint8_t": 1, "int8_t": 1, "char": 1, "uint16_t": 2, "int16_t": 2,
             "uint32_t": 4, "int32_t": 4, "int": 4, "float": 4,
             "uint64_t": 8, "int64_t": 8, "double": 8}
    # 形式 A: (T *)(this + N)  → 字节偏移 N
    m = re.match(r'^\(\s*(\w+)\s*\*\s*\)\s*\(\s*this\s*\+\s*(\d+)\s*\)$', lhs)
    if m:
        off = int(m.group(2))
    else:
        # 形式 B: (T *)this + N  → 字节 = N * sizeof(T)
        m = re.match(r'^\(\s*(\w+)\s*\*\s*\)\s*this\s*\+\s*(\d+)$', lhs)
        if m:
            off = int(m.group(2)) * TYPSZ.get(m.group(1), 4)
        else:
            m = re.match(r'^this\s*\+\s*(\d+)$', lhs)
            if m:
                off = int(m.group(1)) * 4
    if off is None:
        return None
    n = field_name(off, cls)
    if n:
        return "this+%d〔%s〕= %s" % (off, n, short(val, 22))
    # 无名但含常量提示（如 1.0f 位型）仍具信息量
    ch = const_hint(val)
    if ch != val:
        return "this+%d = %s" % (off, ch)
    return None

# 字段读取: v = *(...this + N)   /  v = *(this + N)
def field_read(text, cls):
    m = re.match(r'^(\w+) = \*(.+);$', text)
    if not m:
        return None
    var, ptr = m.group(1), m.group(2).strip()
    if ptr.startswith("(") and ptr.endswith(")"):
        d = 0
        bal = True
        for k, ch in enumerate(ptr):
            if ch == "(":
                d += 1
            elif ch == ")":
                d -= 1
                if d == 0 and k != len(ptr) - 1:
                    bal = False
                    break
        if bal:
            ptr = ptr[1:-1].strip()
    TYPSZ = {"uint8_t": 1, "int8_t": 1, "char": 1, "uint16_t": 2, "int16_t": 2,
             "uint32_t": 4, "int32_t": 4, "int": 4, "float": 4,
             "uint64_t": 8, "int64_t": 8, "double": 8}
    off = None
    m2 = re.match(r'^\(\s*(\w+)\s*\*\s*\)\s*\(\s*this\s*\+\s*(\d+)\s*\)$', ptr)
    if m2:
        off = int(m2.group(2))
    else:
        m2 = re.match(r'^\(\s*(\w+)\s*\*\s*\)\s*this\s*\+\s*(\d+)$', ptr)
        if m2:
            off = int(m2.group(2)) * TYPSZ.get(m2.group(1), 4)
        else:
            m2 = re.match(r'^this\s*\+\s*(\d+)$', ptr)
            if m2:
                off = int(m2.group(1)) * 4
    if off is None or off >= 9000:
        return None
    n = field_name(off, cls)
    return "%s = this+%d〔%s〕" % (var, off, n) if n else None

# 守卫: if ( *((uint8_t *)this + N) != 0 )
def guard(text, cls):
    if not text.startswith("if ("):
        return None
    inner = text[4:].rstrip(")").strip()
    m = re.match(r'^\*\(\s*\(?\s*(\w+)\s*\*\s*\)?\s*(?P<body>\(?\s*this\s*\+\s*\d+\s*\)?)\s*\)\s*(?P<op>[!=]=)\s*(?P<v>\d+)$', inner)
    if not m:
        return None
    TYPSZ = {"uint8_t": 1, "int8_t": 1, "char": 1, "uint16_t": 2, "int16_t": 2,
             "uint32_t": 4, "int32_t": 4, "int": 4, "float": 4,
             "uint64_t": 8, "int64_t": 8, "double": 8}
    mo = re.search(r'this\s*\+\s*(\d+)', m.group("body"))
    if not mo:
        return None
    idx = int(mo.group(1))
    # 判断形态: (T *)this + N  → 下标;  (T *)(this + N) → 字节;  this + N → 字节?
    if re.search(r'\)\s*this\s*\+', inner.replace(" ", "")) or re.match(r'^\(\w+\*\)this\+', inner.replace(" ", "")):
        off = idx * TYPSZ.get(m.group(1), 4)
    elif re.search(r'\)\s*\(\s*this\s*\+', inner):
        off = idx
    else:
        off = idx * 4
    if off is None:
        return None
    n = field_name(off, cls)
    chk = ("≠ 0" if m.group("op") == "!=" else "== 0")
    return "若 this+%d〔%s〕%s" % (off, n, chk) if n else None



READ_R = re.compile(r'^return \*(?P<ptr>.+);$')
def field_read_ret(text, cls):
    m = READ_R.match(text)
    if not m:
        return None
    ptr = m.group("ptr").strip()
    while ptr.startswith("(") and ptr.endswith(")"):
        d = 0
        bal = True
        for k, ch in enumerate(ptr):
            if ch == "(":
                d += 1
            elif ch == ")":
                d -= 1
                if d == 0 and k != len(ptr) - 1:
                    bal = False
                    break
        if not bal:
            break
        ptr = ptr[1:-1].strip()
    TYPSZ = {"uint8_t": 1, "int8_t": 1, "char": 1, "uint16_t": 2, "int16_t": 2,
             "uint32_t": 4, "int32_t": 4, "int": 4, "float": 4,
             "uint64_t": 8, "int64_t": 8, "double": 8}
    off = None
    mm = re.match(r'^\(\s*(\w+)\s*\*\s*\)\s*\(\s*this\s*\+\s*(\d+)\s*\)$', ptr)
    if mm:
        off = int(mm.group(2))
    else:
        mm = re.match(r'^\(\s*(\w+)\s*\*\s*\)\s*this\s*\+\s*(\d+)$', ptr)
        if mm:
            off = int(mm.group(2)) * TYPSZ.get(mm.group(1), 4)
        else:
            mm = re.match(r'^this\s*\+\s*(\d+)$', ptr)
            if mm:
                off = int(mm.group(1)) * 4
    if off is None:
        return None
    if off > 9000:
        # 超出基类区，可能是数组/子对象区，标注为容器引用
        return "返回 this + %d 处指针" % off
    n = field_name(off, cls)
    if n:
        return "返回成员 this+%d〔%s〕" % (off, n)
    return "返回成员 this+%d" % off


def semantic(text, cls):
    best = None
    for m in re.finditer(r'sub_([0-9A-F]{6})', text):
        a = nm_ann(m.group(1))
        if a and (best is None or len(a) > len(best)):
            best = a
    if best:
        return short(best)
    # 虚表调用: (*this + N))(  / (*pArg1 + N))(  / (**x)( ... / (*this)[K]( /
    m = re.search(r'\(\*\s*(?:\([^)]*\)\s*)?(\w+)\s*\+\s*(\d+)\s*\)\s*\)*\s*\(', text)
    if m:
        off = int(m.group(2))
        if off in VT:
            return "调虚槽 +%d：%s" % (off, VT[off])
        s = SLOTMAP.get(str(off))
        if s:
            return "调虚槽 +%d：%s" % (off, short(s, 46))
        return "调虚槽 +%d" % off
    if re.search(r'\(\*this\)\[\d+\]\s*\(', text):
        return "间接/虚函数调用"
    m = re.search(r'\(\s*\*\*\s*(\w+)\s*\)\s*\(\s*\1', text)
    if m:
        return "调 %s 的虚函数（vt+0）" % m.group(1)
    off = byte_off_of(text)
    if off is not None:
        n = field_name(off, cls)
        if n:
            return "this+%d〔%s〕" % (off, n)
    fw = field_write(text, cls)
    if fw:
        return fw
    fr = field_read(text, cls)
    if fr:
        return fr
    fr2 = field_read_ret(text, cls)
    if fr2:
        return fr2
    g = guard(text, cls)
    if g:
        return g
    for g2, s in GLOB.items():
        if g2 in text:
            return s
    m = re.search(r'operator new\((0x[0-9A-Fa-f]+|\d+)u?\)', text)
    if m:
        sz = m.group(1)
        n = int(sz, 16) if sz.lower().startswith("0x") else int(sz)
        return "new(%d 字节) 分配对象" % n
    if re.search(r'\bsprintf|\bstrcpy|\bstrcat|_snprintf', text):
        lit = re.search(r'"([^"]{3,})"', text)
        return "拼字符串" + ("（模板 %s）" % short(lit.group(1), 30) if lit else "")
    # case N -> 包名（若为协议号）
    m = re.match(r'^case (\d+)u?:$', text)
    if m:
        n = int(m.group(1))
        pn = PKT.get(str(n - 1)) or PKT.get(str(n))
        return ("case %d = %s" % (n, pn)) if pn else None
    return None

RET_C = {"-2147483646": "0x80000002(已初始化)", "-2147483640": "0x80000008(内存不足)",
 "-2147483647": "0x80000001(未就绪)", "0x80000000": "0x80000000(失败)",
 "-2147483641": "0x80000007(E_FAIL)"}

def objective(text):
    m = re.match(r'^return (-?\d+);$', text)
    if m:
        v = m.group(1)
        if v == "0":
            return "返回 0"
        if v == "1":
            return "返回 1(成功)"
        if v in RET_C:
            return "返回 " + RET_C[v]
        return None
    if text == "return result;":
        return "返回 result"
    if text == "return this;":
        return "返回 this"
    m = re.match(r'^(\w+) = (-?\d+);$', text)
    if m:
        return "%s = %s" % (m.group(1), m.group(2))
    m = re.match(r'^(\w+) = nullptr;$', text)
    if m:
        return "%s = 空指针" % m.group(1)
    if text == "else":
        return "否则分支"
    if text == "default:":
        return "默认分支"
    m = re.match(r'^LABEL_(\d+):$', text)
    if m:
        return "标签 LABEL_%s（跳转合流点）" % m.group(1)
    m = re.match(r'^\+\+(\w+);$', text)
    if m:
        return "%s 自增" % m.group(1)
    m = re.match(r'^(\w+) \+= (\d+);$', text)
    if m:
        return "%s 前进 %s" % (m.group(1), m.group(2))
    m = re.match(r'^if \( (\w+) != nullptr \)$', text)
    if m:
        return "若 %s 有效（非空）" % m.group(1)
    m = re.match(r'^if \( (\w+) == nullptr \)$', text)
    if m:
        return "若 %s 为空" % m.group(1)
    if text == "if ( result != 0 )":
        return "若结果非 0（成功）"
    return None

# ---------- 客观形态层（v2）：语句/条件/循环/赋值全覆盖 ----------
ASSIGN_R = re.compile(r'^(\*?\(?[\w\[\]\.\+\-\> \*]*?)\)?\s*=\s*(.+);$')

def describe_rhs(rhs):
    r = rhs.strip()
    if r == "nullptr":
        return "空指针"
    if re.match(r'^-?\d+$', r):
        return r
    if re.match(r'^-?\d+\.\d+f?$', r):
        return r
    m = re.match(r'^sub_([0-9A-F]{6})\(', r)
    if m:
        a = nm_ann(m.group(1))
        return ("调 %s" % a) if a else ("调 sub_%s 返回值" % m.group(1))
    m = re.match(r'^\((?:\w|\s|\*)+\)\s*sub_([0-9A-F]{6})\(', r)
    if m:
        a = nm_ann(m.group(1))
        return ("调 %s(带转换)" % a) if a else ("调 sub_%s 返回值" % m.group(1))
    m = re.match(r'^(\w+)\s*\+\s*(\d+)$', r)
    if m:
        return "%s + %s" % (m.group(1), m.group(2))
    m = re.match(r'^(\w+)\s*([+\-*/])\s*(\w+)$', r)
    if m:
        return "%s %s %s" % (m.group(1), m.group(2), m.group(3))
    m = re.match(r'^(\w+)\s*([+\-*/])\s*(\d+)$', r)
    if m:
        return "%s %s %s" % (m.group(1), m.group(2), m.group(3))
    m = re.match(r'^(\w+)\[([^\]]+)\]$', r)
    if m:
        return "取 %s[%s]" % (m.group(1), m.group(2))
    if r.startswith("*(uint"):
        mm = re.search(r'this\s*\+\s*(\d+)', r)
        if mm:
            return "读 this+%s" % mm.group(1)
        return None
    m = re.match(r'^(\w+)\s*->\s*(\w+)$', r)
    if m:
        return "%s->%s" % (m.group(1), m.group(2))
    if re.match(r'^\d+\s*[+\-*/]', r):
        return r
    m = re.match(r'^\((?:\w|\s|\*)+\)\s*(.+)$', r)
    if m:
        inner = m.group(1).strip()
        if re.match(r'^-?\d+$', inner):
            return "转换(%s)" % inner
        if inner.startswith("sub_"):
            return "调 %s" % inner.split('(')[0]
        if re.match(r'^\((\w+) \*\)(.+)$', inner):
            return "取指针"
        return None
    if "(" in r and ")" in r:
        head = r.split("(")[0].strip()
        if re.match(r'^[\w:\.\->]+$', head):
            a = None
            if head.startswith("sub_"):
                a = nm_ann(head[4:])
            return ("调 %s" % a) if a else ("调 %s" % head)
        return None
    if re.match(r'^\w+$', r):
        return r
    return None

def objective2(text):
    if text == "else":
        return "否则分支"
    # for / while / do
    la = loop_ann(text)
    if la:
        return la
    if text == "break;":
        return "跳出循环/分支"
    if text == "continue;":
        return "进入下一轮循环"
    if text == "default:":
        return "默认分支"
    m = re.match(r'^case (-?\d+)u?:$', text)
    if m:
        return "case %s" % m.group(1)
    m = re.match(r'^LABEL_(\d+):$', text)
    if m:
        return "跳转标签 %s" % m.group(1)
    m = re.match(r'^switch \( (.+) \)$', text)
    if m:
        return "按 %s 分派" % short(m.group(1), 30)
    # if 条件
    if text.startswith("if ("):
        tt = re.sub(r'\)\s*\{$', ')', text)
        inner = tt[4:].rstrip(")").strip()
        m = re.match(r'^(\w+) != 0$', inner)
        if m:
            return "若 %s 非 0" % m.group(1)
        m = re.match(r'^(\w+) == 0$', inner)
        if m:
            return "若 %s 为 0" % m.group(1)
        # 成员比较: a->b op c
        m = re.match(r'^(\w+)->(\w+)\s*([!=<>]=?)\s*(.+)$', inner)
        if m:
            return "若 %s.%s %s %s" % (m.group(1), m.group(2), m.group(3), short(m.group(4), 18))
        m = re.match(r'^(\w+) != (\w+)$', inner)
        if m:
            return "若 %s != %s" % (m.group(1), m.group(2))
        m = re.match(r'^(\w+) == (\w+)$', inner)
        if m:
            return "若 %s == %s" % (m.group(1), m.group(2))
        m = re.match(r'^(\w+) < (\w+)$', inner)
        if m:
            return "若 %s < %s" % (m.group(1), m.group(2))
        m = re.match(r'^(\w+) > (\w+)$', inner)
        if m:
            return "若 %s > %s" % (m.group(1), m.group(2))
        m = re.match(r'^(\w+) <= (\w+)$', inner)
        if m:
            return "若 %s <= %s" % (m.group(1), m.group(2))
        m = re.match(r'^(\w+) >= (\w+)$', inner)
        if m:
            return "若 %s >= %s" % (m.group(1), m.group(2))
        m = re.match(r'^(\w+) (&|\|) (\d+)$', inner)
        if m:
            return "若 %s %s %s" % (m.group(1), m.group(2), m.group(3))
        m = re.match(r'^\(?(\w+)(\[[^\]]+\])? & (\d+)\)? != 0$', inner)
        if m:
            return "若 %s 位 %s 测试" % (m.group(1), m.group(3))
        m = re.match(r'^\(?(\w+)(\[[^\]]+\])? & (\d+)\)? == 0$', inner)
        if m:
            return "若 %s 位 %s 清零" % (m.group(1), m.group(3))
        if "||" in inner or "&&" in inner:
            subs = re.split(r'\s*(?:\|\||&&)\s*', inner)
            parts = []
            for sub in subs[:3]:
                mm = re.match(r'^\(?\s*(\w+)->(\w+)\s*([!=<>]=?)\s*([\w\-]+)', sub)
                if mm:
                    parts.append("%s.%s %s %s" % (mm.group(1), mm.group(2), mm.group(3), mm.group(4)))
                else:
                    mm = re.match(r'^\(?\s*(\w+)\s*([!=<>]=?)\s*([\w\-]+)', sub)
                    if mm:
                        parts.append("%s %s %s" % (mm.group(1), mm.group(2), mm.group(3)))
            if parts:
                return "若 " + " 与/或 ".join(parts)
            return "复合条件判定（与/或）"
        if inner.startswith("operator new"):
            return "若 new 分配成功"
        if "sub_" in inner:
            return "若调用结果为真"
        if "nullptr" in inner:
            return "空指针判定"
        return None
    # return
    if text.startswith("return ") and text.endswith(";"):
        inner = text[7:-1].strip()
        if re.match(r'^-?\d+$', inner):
            return None
        d = describe_rhs(inner)
        if d is None:
            return None
        return "返回 " + short(d, 40)
    # 赋值
    m = re.match(r'^([\w\[\]\.\->]+) = (.+);$', text)
    if m:
        lhs, rhs = m.group(1), m.group(2)
        d = describe_rhs(rhs)
        if d is None:
            return None
        return "%s = %s" % (lhs, d)
    # 指针/字段写
    m = re.match(r'^\*(.+?) = (.+);$', text)
    if m:
        return None
    # 数组写
    m = re.match(r'^([\w\.\->]+)\[([^\]]+)\] = (.+);$', text)
    if m:
        return "%s[%s] = %s" % (m.group(1), m.group(2), short(m.group(3), 20))
    # 成员写: x->f = expr;  (对象字段)
    m = re.match(r'^(\w+)->(\w+) = (.+);$', text)
    if m:
        d = describe_rhs(m.group(3))
        if d is None:
            return None
        return "%s.%s = %s" % (m.group(1), m.group(2), d)
    # 自增/自减
    m = re.match(r'^(\+\+|--)(\w+);$', text)
    if m:
        return "%s %s" % (m.group(2), "自增" if m.group(1) == "++" else "自减")
    m = re.match(r'^(\w+)\s*([+\-*/]=)\s*(\w+);$', text)
    if m:
        return "%s %s %s" % (m.group(1), m.group(2), m.group(3))
    return None


def localdecl_ann(text):
    """局部变量声明（带初始化）—— 描述初值来源"""
    m = re.match(r'^(?:struct\s+)?[\w:]+\s*\*?\s*(\w+)\s*=\s*(.+);$', text)
    if not m:
        return None
    var, rhs = m.group(1), m.group(2).strip()
    # 指针初始化
    if re.match(r'^\(\s*\w+.*\*\s*\)', rhs):
        return None
    if "timeGetTime" in rhs:
        return "%s = timeGetTime 帧时刻" % var
    if "GetTickCount" in rhs:
        return "%s = GetTickCount 时刻" % var
    d = describe_rhs(rhs)
    if d is None:
        return None
    return "%s = %s" % (var, short(d, 40))

def buffer_ann(text):
    """缓冲/内存操作 —— memset/拷贝/缓冲槽写"""
    m = re.match(r'^memset\((\w+) \+ (\d+), (\d+), (0x[0-9A-Fa-f]+|\d+)u?\);$', text)
    if m:
        return "清零 %s+%s 起 %s 字节" % (m.group(1), m.group(2), m.group(4))
    m = re.match(r'^memset\((\w+), (\d+), (0x[0-9A-Fa-f]+|\d+)u?\);$', text)
    if m:
        return "清零 %s 起 %s 字节" % (m.group(1), m.group(3))
    m = re.match(r'^qmemcpy\((.+?), (.+?), (\d+)\);$', text)
    if m:
        return "内存块拷贝 %s 字节" % m.group(3)
    m = re.match(r'^\*\(\((\w+) \*\)(\w+) \+ (\d+)\) = (.+);$', text)
    if m:
        d = describe_rhs(m.group(4))
        if d is None:
            return None
        return "%s[%s] = %s" % (m.group(2), m.group(3), short(d, 24))
    m = re.match(r'^\*\((\w+) \*\)(\w+) = (.+);$', text)
    if m:
        d = describe_rhs(m.group(3))
        if d is None:
            return None
        return "*%s = %s" % (m.group(2), short(d, 24))
    m = re.match(r'^(\w+) = \*\(uint16_t \*\)\((\w+) \+ (\d+)\);$', text)
    if m:
        return "%s = 读 %s+%s 的 16 位值" % (m.group(1), m.group(2), m.group(3))
    return None

def main():
    rel = sys.argv[1].replace("\\", "/").split("src/")[-1]
    path = os.path.join(ROOT, "src", rel)
    lines = io.open(path, encoding="utf-8", errors="replace").read().split("\n")
    notes = []
    cur_cls = ""
    cur_va = None
    for i, l in enumerate(lines, 1):
        s = l.strip()
        if s.startswith("//"):
            m = re.match(r'// 0x([0-9A-F]{6})\s+(\w+?)__vmt', s)
            if m:
                cur_va = m.group(1)
                cur_cls = m.group(2)
            elif re.match(r'// 0x[0-9A-F]{6}\s+(\w+)', s):
                cur_va = re.match(r'// 0x([0-9A-F]{6})', s).group(1)
                cur_cls = re.match(r'// 0x[0-9A-F]{6}\s+(\w+)', s).group(1)
            continue
        if "//" in l:
            continue
        if not s or s in ("{", "}"):
            continue
        # 跳过函数定义行（改由 funcdef 规则统一处理）
        is_funcdef = bool(re.match(r'^(?:int|void|char|float|double|uint\w*|unsigned|signed|long|short|bool|size_t|DWORD|WORD|BYTE|__int64|struct|LONG|__int16|__int8)\b[^;]*\([^;]*\)\s*$', s) and not s.endswith(";"))
        if is_funcdef:
            fa = funcdef_ann(s, cur_va)
            if fa:
                notes.append([i, fa])
            continue
        if s.startswith("case ") or s.startswith("default:") or s in ("else", "do", "break;", "continue;"):
            a = semantic(s, cur_cls) if s.startswith("case ") else (objective2(s) or semantic(s, cur_cls))
            if a:
                notes.append([i, a])
            continue
        ann = semantic(s, cur_cls) or objective(s) or objective2(s) or localdecl_ann(s) or buffer_ann(s)
        if ann:
            ann = ann.replace('"', '').replace("'", "").replace("/*", "").replace("*/", "")
            if ann.startswith("0x"):
                ann = "·" + ann
            if BAN.match(ann):
                continue
            notes.append([i, ann])
    out = os.path.join(ROOT, "work", "_t1b_" + rel.replace("/", "_") + ".json")
    json.dump({"file": rel, "notes": notes}, io.open(out, "w", encoding="utf-8"), ensure_ascii=False)
    print("%s: %d notes" % (rel, len(notes)))

if __name__ == "__main__":
    main()

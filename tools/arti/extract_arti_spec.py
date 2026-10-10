"""Extract the configuration attributes of every ARTI definition from the AUTOSAR PDFs.

Run from the repository root:  python -m tools.arti.extract_arti_spec
Requires PyMuPDF (pip install pymupdf). Writes tools/arti/arti_spec.json, which
gen_arti_def.py reads. The JSON is committed, so PyMuPDF is only needed to refresh it.

Sources (doc/ARTI/):
  AUTOSAR_CP_SWS_ARTI.pdf  chapter 10   -> ArtiGeneric, ArtiValues (ArtiRte is extracted but unused)
  AUTOSAR_SWS_OS.pdf       section 10.4 -> ArtiHardware, ArtiOs

For each container / parameter / reference the PDF tables give: multiplicity,
post-build variant multiplicity/value, multiplicity and value configuration
classes, and scope. Container multiplicities come from the parent's
"Included Containers" table.
"""
import json
import re
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
PDF_DIR = ROOT / "doc" / "ARTI"
OUT = Path(__file__).with_name("arti_spec.json")

START = {"Parameter Name", "Container Name", "Name", "SWS Item"}
CONT = {"", "Multiplicity Configuration Class", "Value Configuration Class", "Scope / Dependency",
        "Post-Build Variant Value", "Post-Build Variant Multiplicity", "Regular Expression", "Default value",
        "Range", "Type", "Multiplicity", "Description", "Parent Container"}
CLASS_NAME = {"Pre-compile time": "PRE-COMPILE", "Link time": "LINK", "Post-build time": "POST-BUILD"}


def clean(cell):
    if cell is None:
        return None
    cell = cell.replace("\n", " ").strip()
    return "-" if cell.startswith("�") or cell == "–" else cell


def tables(doc, first, last):
    for i in range(first, last):
        for table in doc[i].find_tables().tables:
            yield i + 1, [[clean(c) for c in row] for row in table.extract()]


def collect(doc, first, last):
    recs, included, cur = [], [], None
    for page, rows in tables(doc, first, last):
        if not rows:
            continue
        key = rows[0][0]
        if key in ("Included Parameters", "Included Containers"):
            included.append((key, rows))
            cur = None
        elif key in START:
            cur = {"rows": list(rows)}
            recs.append(cur)
        elif cur is not None and key in CONT:
            cur["rows"].extend(rows)
    return recs, included


def mult(text):
    if not text:
        return None
    lo, _, hi = text.partition("..")
    return [int(lo), -1 if hi == "*" else int(hi or lo)]


def parse(rec):
    out, last = {}, None
    for row in rec["rows"]:
        key = row[0] or ""
        vals = [c for c in row[1:] if c]
        if key:
            last = key
        if key in ("Parameter Name", "Container Name", "Name"):
            out.setdefault("name", vals[0].split("[")[0].replace(" ", ""))
        elif key in ("Multiplicity Configuration Class", "Value Configuration Class") or (
                key == "" and last in ("Multiplicity Configuration Class", "Value Configuration Class")):
            if len(vals) >= 2 and vals[1] == "X":
                variant = vals[2] if len(vals) > 2 else ""
                out.setdefault("mc" if last.startswith("Multiplicity") else "vc", []).append(
                    [CLASS_NAME[vals[0]], variant])
        elif key in ("Multiplicity", "Parent Container", "Post-Build Variant Multiplicity",
                     "Post-Build Variant Value", "Scope / Dependency"):
            out[key] = " ".join(vals)
    return out


def flag(text):
    return None if text is None else text == "true"


def normalise(rec):
    p = parse(rec)
    scope = re.search(r"scope:\s*(\w+)", p.get("Scope / Dependency", ""))
    return {
        "parent": p.get("Parent Container"),
        "mult": mult(p.get("Multiplicity")),
        "pbm": flag(p.get("Post-Build Variant Multiplicity")),
        "pbv": flag(p.get("Post-Build Variant Value")),
        "mc": p.get("mc", []),
        "vc": p.get("vc", []),
        "scope": scope.group(1).upper() if scope else None,
    }, p.get("name")


def main():
    import fitz
    spec = {}
    sws = fitz.open(str(PDF_DIR / "AUTOSAR_CP_SWS_ARTI.pdf"))
    osd = fitz.open(str(PDF_DIR / "AUTOSAR_SWS_OS.pdf"))
    first = next(i for i in range(200, len(osd)) if "ECUC_Arti_00061" in osd[i].get_text())
    last = next(i for i in range(first + 1, len(osd))
                if "Published Information" in osd[i].get_text() and "chapter 10.3" in osd[i].get_text())
    for doc, a, b in ((sws, 45, 106), (osd, first, last + 1)):
        recs, included = collect(doc, a, b)
        for rec in recs:
            entry, name = normalise(rec)
            if name:
                spec.setdefault(name, {}).update(entry)
        for kind, rows in included:
            if kind == "Included Containers":
                for row in rows[1:]:
                    name = (row[0] or "").replace(" ", "")
                    if name in spec or name.startswith("Arti"):
                        spec.setdefault(name, {})["container_mult"] = mult(row[1])
    # ArtiOsTaskInstance's name cell is split over a page break and is missed by the table scan.
    spec.setdefault("ArtiOsTaskInstance", {}).setdefault("container_mult", [0, -1])
    json.dump(spec, open(OUT, "w", encoding="utf-8"), indent=1, sort_keys=True)
    print(f"{len(spec)} entries -> {OUT}")


if __name__ == "__main__":
    sys.exit(main())

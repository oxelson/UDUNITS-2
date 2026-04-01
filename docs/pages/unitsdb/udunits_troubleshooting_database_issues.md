
# 9. Troubleshooting Database Issues

This section summarizes common problems encountered when working with the UDUNITS-2 XML unit database, based on patterns observed in the Unidata support archives, mailing lists, and issue tracker.

Most errors arise from inconsistencies between XML definitions, unit grammar, dimensional relationships, or environment configuration.

Troubleshooting typically involves verifying:

- XML structure and imports
- dimensional consistency of definitions
- correct unit grammar
- correct environment variables and database paths

The `udunits2` CLI utility can assist in debugging by revealing database issues using the `-r` option.

Example:

```bash
udunits2 -r
```

---

## 9.1 Common Problems and Resolutions

| Symptom | Likely Cause | Diagnosis | Resolution |
|--------|-------------|-----------|-----------|
| unit not recognized | missing or incorrectly imported definition | verify XML `<import>` chain and `<unit>` element | add definition or correct import path |
| unexpected conversion result | incorrect dimensional relationship or scale factor | inspect `<def>` expression | correct dimensional formula |
| units not convertible | incompatible base dimensions | check dimensional consistency | revise definition to ensure compatible dimensions |
| parsing failure | syntax error in unit expression or XML | validate grammar and XML structure | correct formatting or expression |
| database fails to load | incorrect XML path or environment configuration | verify `UDUNITS2_XML_PATH` or default install location | update environment variable or provide explicit path |
| symbol interpreted incorrectly | ambiguity between symbols and names | confirm canonical unit symbol or alias | define alias or use standard symbol |
| previously valid unit no longer works | differences between UDUNITS-1 and UDUNITS-2 databases | compare legacy definitions | add local alias definitions |

---

## 9.2 Missing or Unrecognized Units

A frequent issue occurs when a unit symbol used in legacy systems is not included in the default UDUNITS-2 database.

Example:

- `kph` interpreted as **kilophot**, not kilometers per hour
- UDUNITS-1 allowed informal abbreviations not included in the UDUNITS-2 XML database

Resolution typically involves defining a local alias:

```xml
<unit-system>
    <unit>
        <def>kilometers/hour</def>
        <aliases>
            <name>
                <singular>kph</singular>
            </name>
        </aliases>
    </unit>
</unit-system>
```

and importing the file:

```xml
<import>localunits.xml</import>
```

Common problematic abbreviations:

| ambiguous symbol | intended meaning | preferred UDUNITS form |
|------------------|------------------|------------------------|
| F | degrees Fahrenheit | degF |
| mph | miles per hour | mile/hour |
| inHg | inches of mercury | in_Hg |
| mB | millibar | mbar |

---

## 9.3 Incorrect Conversions

Unexpected conversion factors usually indicate an incorrect `<def>` expression or dimensional inconsistency.

Common causes:

- incorrect exponent
- missing scale factor
- incorrect base unit reference
- mixing offset units improperly

Example incorrect definition:

```xml
<def>meter^2 second</def>
```

Correct form:

```xml
<def>meter^2/second</def>
```

Dimensional incompatibility will cause conversion checks to fail even when units appear related.

---

## 9.4 XML Syntax and Grammar Errors

Because the database is XML-based, structural errors may prevent loading or parsing.

Common issues:

- missing closing tags
- incorrect nesting of `<unit>` elements
- invalid characters
- malformed `<def>` expressions
- incorrect exponent syntax

Validation strategies:

- validate XML against schema
- check well‑formedness using standard XML tools
- test unit expressions directly using the CLI

Example:

```bash
udunits2
You have: kg*m/s^2
```

---

## 9.5 Database Location and Environment Configuration

The database must be discoverable at runtime.

Common configuration problems:

- incorrect install location
- environment variables not set
- incorrect relative path usage
- platform-specific filesystem differences

UDUNITS uses a default compiled-in path, but can also locate the database using the `UDUNITS2_XML_PATH` environment variable.

Example:

```bash
export UDUNITS2_XML_PATH=/usr/local/share/udunits/udunits2.xml
```

---

## 9.6 Debugging Workflow

Recommended diagnostic sequence:

1. Verify XML well-formedness
2. Confirm unit definition exists
3. Verify dimensional consistency
4. Test expression with CLI
5. Check environment variable configuration
6. Inspect aliases and symbol conflicts

Typical CLI workflow:

```bash
udunits2 -r
udunits2 -H "m/s" -W "km/h"
```

---

## 9.7 Best Practices for Avoiding Database Errors

- prefer canonical SI names and symbols
- avoid ambiguous abbreviations
- define aliases explicitly
- maintain consistent dimensional relationships
- validate XML before deployment
- keep custom definitions isolated in separate imported files
- avoid circular references between derived units
- document all custom units


# 5. Core Database Components

The UDUNITS-2 database defines a comprehensive and extensible catalog of scientific units using a structured XML representation. Core components describe the fundamental measurement system, relationships between units, and linguistic flexibility needed for parsing and interpreting unit expressions.

The default database (`udunits2.xml`) includes definitions for SI base units, derived units, physical constants, and multiple naming variants. Together, these components enable dimensional consistency, symbolic manipulation, and reliable conversion between compatible units.

---

## 5.1 Base Units

Base units represent the fundamental dimensions of measurement. These units form the dimensional foundation upon which all derived units are defined. Each base unit corresponds to an independent physical dimension, allowing UDUNITS-2 to perform dimensional analysis when evaluating unit compatibility.

The default database follows the International System of Units (SI) base unit definitions. Each base unit is represented in the XML database with attributes describing its canonical symbol, name, and dimensional identity.

### Included SI Base Units

| Quantity | Unit Name | Symbol |
|---------|-----------|--------|
| Length | meter | m |
| Mass | kilogram | kg |
| Time | second | s |
| Electric current | ampere | A |
| Thermodynamic temperature | kelvin | K |
| Amount of substance | mole | mol |
| Luminous intensity | candela | cd |

### Characteristics

* Each base unit defines a primary dimension in the UDUNITS dimensional model.
* Base units do not reference other units in their definitions.
* All derived units ultimately resolve to combinations of these base dimensions.
* Dimensional vectors constructed from base units are used internally to determine compatibility between units.

Example XML structure:

```xml
<unit>
    <name>meter</name>
    <symbol>m</symbol>
    <dimension>L</dimension>
</unit>
```

---

## 5.2 Derived Units

Derived units are defined in terms of combinations of base units. These definitions may include multiplication, division, and exponentiation, enabling the representation of complex physical relationships.

UDUNITS-2 stores derived units as expression-based definitions that resolve to dimensional equivalence classes. This allows conversions between units that represent the same physical dimension even if their symbolic expressions differ.

### Examples of Derived Units

| Unit | Definition | Dimension |
|------|------------|-----------|
| newton (N) | kg·m·s⁻² | force |
| joule (J) | N·m | energy |
| watt (W) | J·s⁻¹ | power |
| pascal (Pa) | N·m⁻² | pressure |

### Definition Structure

Derived unit definitions typically include:

* symbolic expressions referencing other units
* dimensional equivalence relationships
* optional scaling factors
* optional offsets (for temperature units)

Example XML definition:

```xml
<unit>
    <name>newton</name>
    <symbol>N</symbol>
    <definition>kilogram meter second-2</definition>
</unit>
```

### Dimensional Consistency

Internally, UDUNITS-2 reduces derived unit expressions to dimensional vectors constructed from base units. Two units are considered compatible if their dimensional representations are equivalent.

Examples of compatible expressions:

```
joule = newton meter
joule = kilogram meter2 second-2
```

Both expressions resolve to identical dimensional structure.

---

## 5.3 Constants

The UDUNITS database includes physical constants that support unit definitions and conversions. Constants provide numerical scaling factors used in derived unit expressions or domain-specific unit systems.

Constants are typically defined using high-precision numerical values and may reference internationally recognized standards.

### Examples of Constants

| Constant | Value | Role |
|----------|-------|------|
| standard gravity | 9.80665 m·s⁻² | used in force and weight calculations |
| speed of light | 299792458 m·s⁻¹ | used in radiation and physics units |

Constants allow units to be defined relative to physical phenomena rather than strictly in terms of SI primitives.

Example XML structure:

```xml
<constant>
    <name>standard_gravity</name>
    <value>9.80665</value>
    <unit>meter second-2</unit>
</constant>
```

Constants may also be referenced within unit definitions:

```xml
<unit>
    <name>gee</name>
    <definition>standard_gravity</definition>
</unit>
```

---

## 5.4 Aliases and Symbols

UDUNITS-2 supports multiple naming conventions for the same unit through aliases and symbol definitions. This flexibility enables robust parsing of unit expressions across scientific domains, regional spelling differences, and legacy notation styles.

Aliases allow different textual representations to resolve to the same underlying unit object.

### Supported Variations

* abbreviations
* plural forms
* alternative spellings
* legacy names
* symbol variants

### Examples

| Canonical Name | Supported Variants |
|----------------|-------------------|
| meter | metre |
| liter | litre |
| second | sec, s |
| kilogram | kg |
| kelvin | K |

Example XML alias structure:

```xml
<unit>
    <name>meter</name>
    <symbol>m</symbol>

    <aliases>
        <alias>metre</alias>
    </aliases>
</unit>
```

Plural forms are often automatically recognized, reducing the need to explicitly define every variation:

```
meters
metres
seconds
joules
```

### Parsing Benefits

Alias support improves interoperability by:

* enabling flexible unit string parsing
* accommodating regional spelling differences
* supporting legacy scientific datasets
* reducing ambiguity in textual unit representations

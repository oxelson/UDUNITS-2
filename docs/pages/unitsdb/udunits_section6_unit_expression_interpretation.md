
# 6. Unit Expression Interpretation

UDUNITS-2 supports a rich grammar for expressing scientific units in textual form. These expressions are parsed into an internal representation that encodes both **dimensional structure** and **scaling factors**, enabling consistent interpretation, conversion, and validation of units.

Expression interpretation relies primarily on the UDUNITS-2 parser (`parser.y`) and the unit system created from the XML database at initialization (via `ut_read_xml()`).

The resulting parsed representation is used by functions such as:

- `ut_parse()`
- `ut_get_converter()`
- `ut_are_convertible()`

These functions allow applications to transform textual unit expressions into machine-interpretable structures and determine compatibility between units.

---

## 6.1 Parsing Grammar

UDUNITS-2 implements a formal grammar for unit expressions supporting arithmetic structure and scale modifiers. Expressions are parsed into a symbolic representation consisting of:

* base dimensions
* exponent values
* scale factors
* offsets (for certain units such as temperature)

Supported grammatical constructs include:

### Multiplication

Multiplication combines units into compound units.

Supported operators:

```
*
.
(space)
```

Examples:

```
N*m
kg m
Pa*s
```

These are interpreted as products of unit dimensions.

---

### Division

Division expresses units in ratio form.

Operator:

```
/
```

Examples:

```
m/s
kg/m^3
W/m^2
```

Division produces negative exponents in the internal dimensional representation.

---

### Exponentiation

Units may be raised to integer or rational powers.

Operator:

```
^
```

Examples:

```
m^2
s^-1
kg*m^2/s^2
```

Exponentiation is applied to the immediately preceding unit or parenthetical expression.

---

### Parentheses

Parentheses allow grouping to control order of operations.

Examples:

```
(kg*m)/s^2
kg*(m/s^2)
(W/m^2)/sr
```

Grouping ensures expressions are interpreted consistently regardless of textual formatting.

---

### Numeric Scale Factors

Numeric constants may appear in expressions and are interpreted as multiplicative scale factors.

Examples:

```
1000 m
1e-3 kg
2.54 cm
```

Scale factors are combined with unit definitions to produce normalized representations.

Example:

```
1000 m = 1 km
```

Internally, the scale factor is stored separately from the dimensional structure.

---

### Temperature Units with Offsets

Some units include offsets rather than pure scaling factors.

Example:

```
degC
degF
```

Temperature conversions require affine transformations rather than simple multiplicative scaling.

UDUNITS-2 internally represents these using converters that include both scale and offset parameters.

---

### Expression Examples

| Expression | Interpretation |
|-----------|---------------|
| `kg*m/s^2` | force dimension |
| `W/m^2` | radiative flux |
| `degC` | temperature with offset |
| `m^3/s` | volumetric flow rate |
| `kg/(m*s)` | dynamic viscosity |

---

## 6.2 Compatibility Determination

UDUNITS-2 determines unit compatibility by comparing the **dimension vectors** associated with parsed unit expressions.

Each unit is internally represented as:

```
scale_factor × product(base_dimension^exponent)
```

Example:

```
N = kg·m·s⁻²
```

Two units are considered compatible if their base dimension exponents are identical after normalization.

---

### Example: Derived Unit Equivalence

Newton is defined in the database as:

```
N = kg·m·s⁻²
```

When parsing:

```
kg*m/s^2
```

UDUNITS-2 constructs the same dimensional representation, allowing equivalence to be detected automatically.

Example workflow:

```
ut_unit* u1 = ut_parse(system, "N", UT_UTF8);
ut_unit* u2 = ut_parse(system, "kg*m/s^2", UT_UTF8);

ut_are_convertible(u1, u2) → true
```

---

### Dimensional Analysis Process

Compatibility determination proceeds as follows:

1. Parse each unit expression into symbolic form
2. Reduce derived units into base dimensions
3. Normalize scale factors
4. Compare exponent vectors
5. Determine whether a conversion exists

If dimensions match, a converter may be created:

```
cv_converter* converter =
    ut_get_converter(unit1, unit2);
```

If dimensions differ, conversion fails:

```
"meter" ↔ "second" → incompatible
```

---

### Examples of Compatible Units

| Unit A | Unit B |
|-------|-------|
| `m` | `km` |
| `Pa` | `N/m^2` |
| `J` | `kg*m^2/s^2` |
| `W` | `J/s` |
| `Hz` | `s^-1` |

---

### Examples of Incompatible Units

| Unit A | Unit B |
|-------|-------|
| `m` | `kg` |
| `s` | `K` |
| `Pa` | `m` |
| `J` | `C` |

---

### Relationship to Database Definitions

Compatibility relies on definitions provided in the XML database:

```
<unit>
    <name>newton</name>
    <definition>kg·m/s^2</definition>
</unit>
```

The parser resolves references recursively, ensuring derived units ultimately reduce to base dimensions.

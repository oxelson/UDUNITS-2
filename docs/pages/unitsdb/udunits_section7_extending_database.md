# 7. Extending the Database

The UDUNITS-2 database is designed to be extensible through modification
or augmentation of the XML unit definition files. Users can introduce
domain-specific units, aliases, prefixes, and relationships without
modifying the core library code.

Extensions are typically implemented by creating additional XML files
that define new units and importing them into the primary unit database
using the `<import>` mechanism.

Because UDUNITS enforces dimensional consistency internally, any custom
additions must define units in terms of existing dimensions or base
units.

Primary references: \* UDUNITS-2 XML database structure \*
`udunits2.xml` default database file \* XML parsing handled via
`ut_read_xml()` in the C API

------------------------------------------------------------------------

## 7.1 Adding Custom Units

Custom units are introduced by defining new XML elements that describe
how the unit relates to existing base or derived units.

### Step 1: Create a new XML definition file

Example:

``` xml
<unit>
    <name>furlong</name>
    <symbol>fur</symbol>
    <definition>201.168 meter</definition>
</unit>
```

Scaled unit:

``` xml
<unit>
    <name>kilowatt_hour</name>
    <symbol>kW·h</symbol>
    <definition>1000 watt hour</definition>
</unit>
```

Alias:

``` xml
<alias>
    <name>sec</name>
    <unit>second</unit>
</alias>
```

### Step 2: Define dimensional relationship

Each unit must resolve to a valid dimensional expression supported by
the UDUNITS system.

Examples:

    newton = kilogram meter / second^2
    joule = newton meter
    watt = joule / second

### Step 3: Import the custom file into the main database

Example:

``` xml
<import>custom_units.xml</import>
```

Typical structure:

    udunits2.xml
        imports:
            si.xml
            cgs.xml
            accepted.xml
            custom_units.xml

Initialization:

``` c
ut_system* system = ut_read_xml(NULL);
```

------------------------------------------------------------------------

## 7.2 Maintaining Dimensional Consistency

UDUNITS enforces dimensional compatibility through its internal
representation of unit dimensions.

### Guidelines

#### Avoid circular definitions

Invalid:

``` xml
<unit>
    <name>foo</name>
    <definition>bar</definition>
</unit>

<unit>
    <name>bar</name>
    <definition>foo</definition>
</unit>
```

#### Maintain dimensional balance

    newton = kilogram meter / second^2

#### Reuse existing base definitions where possible

Preferred:

    mile = 1609.344 meter

Avoid unnecessary indirection:

    mile = 5280 foot
    foot = 0.3048 meter

#### Validate using the UDUNITS parser

    udunits2 -H "furlong"
    udunits2 -H "furlong per fortnight"

------------------------------------------------------------------------

## 7.3 Versioning Considerations

Changes to the unit database may affect parsing behavior and conversion
results.

### Impact on parsing results

Ambiguous names:

    ton

Better:

    metric_ton
    short_ton
    long_ton

### Impact on conversion factors

    international_foot = 0.3048 meter
    survey_foot = 1200/3937 meter

### Backward compatibility

Prefer introducing new units rather than modifying existing definitions:

    <unit>
        <name>foot_survey</name>
        <definition>1200/3937 meter</definition>
    </unit>

------------------------------------------------------------------------

### Recommended practices

-   version control custom XML files
-   document rationale for unit definitions
-   test parsing behavior after updates
-   maintain consistent naming conventions

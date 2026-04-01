
# 4. Loading the Database

The UDUNITS-2 database is loaded at runtime by parsing one or more XML files that define units, prefixes, dimensions, and relationships among units. The loading process constructs an in-memory representation of a **unit system** (`ut_system`) that is used by the API for unit parsing, compatibility checking, and unit conversion.

The database is typically loaded once during application initialization and then reused throughout the lifetime of the process.

---

## 4.1 Initialization Process

### Overview

The UDUNITS-2 library provides functions for reading XML database files and creating an internal representation of the unit system. This representation encodes:

* dimensional relationships among units
* definitions of base and derived units
* scale factors and offsets
* prefixes and aliases
* imported definitions from modular XML files

The central function for loading the database is:

```c
ut_system* ut_read_xml(const char* path);
```

This function parses the XML database and returns a pointer to a `ut_system` object, which serves as the root container for all unit definitions.

### Loading Workflow

1. Locate the XML database file

   The application determines the XML database file path. This may be:

   * the default system-installed database
   * a user-specified path
   * a customized database file

2. Parse XML structure

   The XML file is processed according to the UDUNITS-2 schema. During parsing:

   * `<unit>` elements define base or derived units
   * `<dimension>` elements establish dimensional relationships
   * `<prefix>` elements define scaling prefixes
   * `<import>` elements include definitions from additional files
   * `<alias>` elements define alternative names or symbols

3. Construct internal model

   The parser constructs an in-memory representation of the unit system:

   * dimension vectors are created
   * scale and offset transformations are registered
   * unit symbols and names are indexed for lookup
   * relationships between units are resolved

   The resulting structure is stored in a `ut_system` object.

4. Validate definitions

   The parser validates consistency across unit definitions:

   * dimensional compatibility
   * absence of cyclic dependencies
   * valid prefix usage
   * consistency of scale and offset relationships

5. Return initialized unit system

   On success, `ut_read_xml()` returns a pointer to a fully initialized `ut_system` object that can be used throughout the API.

Example initialization:

```c
ut_system* system = ut_read_xml(NULL);

if (system == NULL) {
    fprintf(stderr, "Failed to load UDUNITS database\n");
    exit(EXIT_FAILURE);
}
```

Passing `NULL` typically causes the library to locate the default installed XML database.

---

### Internal Representation: `ut_system`

The `ut_system` structure encapsulates:

* the registry of known units
* dimension definitions
* prefix definitions
* conversion relationships
* imported modules

All unit parsing and conversion operations operate relative to a `ut_system` instance.

Typical usage pattern:

1. initialize system using `ut_read_xml()`
2. parse unit strings using `ut_parse()`
3. obtain converters using `ut_get_converter()`
4. release resources using `ut_free_system()`

---

### Error Handling During Load

Errors encountered during database loading may include:

* malformed XML
* schema violations
* undefined referenced units
* incompatible dimensional definitions
* duplicate symbols or names
* missing imported files

When errors occur:

* `ut_read_xml()` returns `NULL`
* detailed diagnostics may be available via the UDUNITS error message handler
* applications should check the return value before proceeding

Example:

```c
ut_system* sys = ut_read_xml("units.xml");

if (!sys) {
    fprintf(stderr, "Error loading UDUNITS database\n");
}
```

---

## 4.2 Custom Database Loading

UDUNITS-2 allows applications to use alternative XML database files instead of the default installed database. This supports:

* domain-specific unit extensions
* overriding definitions
* experimental or specialized unit systems
* controlled vocabularies for scientific projects

Custom databases may extend or replace portions of the default definitions.

---

### Specifying a Custom Database Path

Applications can explicitly specify the XML file to load:

```c
ut_system* sys = ut_read_xml("/path/to/custom-units.xml");
```

The specified file may:

* define a complete standalone database
* import the standard database and extend it
* override specific unit definitions

---

### Environment Variable Configuration

UDUNITS-2 supports environment variables that influence database location. These allow runtime configuration without modifying application code.

Typical workflow:

```bash
export UDUNITS2_XML_PATH=/path/to/custom-units.xml
```

Applications that call:

```c
ut_read_xml(NULL);
```

will then load the database from the configured location.

This approach is useful for:

* reproducible environments
* deployment configuration
* containerized workflows
* shared scientific infrastructure

---

### Extending Existing Definitions

Custom XML files can import the standard database and add new unit definitions.

Example:

```xml
<unit-system>
    <import href="udunits2.xml"/>

    <unit>
        <name>solar_flux_unit</name>
        <symbol>sfu</symbol>
        <definition>1e-22 W m-2 Hz-1</definition>
    </unit>
</unit-system>
```

This approach preserves compatibility with the standard database while introducing domain-specific units.

---

### Overriding Existing Units

A custom XML file may redefine an existing unit symbol or name. Care should be taken when overriding definitions, as this may affect compatibility with existing software or datasets.

Use cases include:

* legacy compatibility
* project-specific conventions
* controlled vocabulary enforcement

---

### Example Workflow

1. Copy the standard XML database:

```bash
cp udunits2.xml custom-units.xml
```

2. Modify definitions:

```xml
<unit>
    <name>ppm_co2</name>
    <definition>1e-6</definition>
</unit>
```

3. Load the modified database:

```c
ut_system* sys = ut_read_xml("custom-units.xml");
```

4. Use the customized unit system throughout the application.

---

### Best Practices

* prefer extending rather than replacing the standard database
* maintain dimensional consistency when defining new units
* validate XML files before deployment
* document custom definitions for reproducibility
* version-control custom XML databases

---

This loading mechanism allows UDUNITS-2 to support both standardized unit definitions and specialized domain extensions while preserving a consistent dimensional framework.

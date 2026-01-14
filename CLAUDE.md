# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Overview

This is a GTK4 tutorial repository following the guide at https://toshiocp.github.io/Gtk4-tutorial/index.html. The codebase contains example C programs demonstrating GTK4 application development, progressing from basic application creation to more advanced features.

## Build and Compile

This project uses GTK4 (version 4.20.3 on the current system) and compiles C programs directly using gcc with pkg-config.

### Compiling Programs

To compile any GTK4 C program:

```bash
gcc `pkg-config --cflags gtk4` <source_file.c> `pkg-config --libs gtk4` -o <output_name>
```

Example:
```bash
gcc `pkg-config --cflags gtk4` pr1.c `pkg-config --libs gtk4` -o pr1
gcc `pkg-config --cflags gtk4` pr2.c `pkg-config --libs gtk4` -o pr2
```

### Running Programs

Execute the compiled binaries directly:
```bash
./pr1
./pr2
```

## Code Structure

The repository contains standalone GTK4 example programs (pr1.c, pr2.c, etc.) that progressively demonstrate GTK4 concepts:

- **pr1.c**: Minimal GTK4 application - creates a GtkApplication without a window or activation handler
- **pr2.c**: GtkApplication with activation signal - demonstrates connecting to the "activate" signal using g_signal_connect()

### Application ID Convention

GTK applications use reverse-DNS style application IDs following the pattern:
```
com.github.motoshira.pr<N>
```

### GTK4 Application Lifecycle

All examples follow this basic pattern:
1. Create GtkApplication with `gtk_application_new()`
2. Optionally connect signal handlers (e.g., "activate" signal)
3. Run the application with `g_application_run()`
4. Clean up with `g_object_unref()`
5. Return the application status code

## License

This project is licensed under the MIT License.

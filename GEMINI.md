# Gemini Workspace Configuration for ZMK

This file guides the Gemini agent on how to interact with this ZMK configuration repository.

## About This Project

This repository contains a personal ZMK firmware configuration for one or more custom keyboards.

## Key Files

When making changes, these are the most important files:

-   `config/*.keymap`: The core keymap definition. This is where you'll find the layout of keys and layers.
-   `config/defines.h`: Contains custom C macros for aliases, shortcuts, and complex key behaviors to improve keymap readability.
-   `config/layers.h`: Uses C macros to define the keyboard layers, making the `.keymap` file cleaner and more structured.
-   `config/*.conf`: Kconfig settings for the board. Used to enable or disable hardware features like OLED screens, encoders, or underglow.
-   `config/*.dtsi` (if present): Devicetree overlays for defining more complex hardware interactions, such as combos, macros, or custom sensor behavior.
-   `build.yaml`: Defines the matrix of boards and shields to be built by the GitHub Actions workflow.
-   `west.yml`: Manages the dependencies of the project, including the ZMK firmware itself.
-   `Justfile`: Contains a set of commands for common tasks.

## Common Workflows & Commands

Here are the essential commands for working with this project.

### Building Firmware

This project uses `just` to simplify the build process. To build the firmware for all boards defined in `build.yaml`, run:

```bash
just build
```

To build for a specific board, you may need to inspect the `Justfile` for the correct command.

The compiled firmware will be located in the `build/zephyr/` directory.

### Updating Dependencies

To pull the latest changes for ZMK and other dependencies defined in `west.yml`:

```bash
west update
```

## Coding Conventions

-   When adding new hardware features, first enable them in the `config/*.conf` file.
-   Keep layers and behaviors logically separated in the `.keymap` file for readability.

### Helper Macros for Readability

This configuration makes extensive use of C preprocessor macros to create more readable and maintainable `.keymap` files.

-   **Custom Behaviors & Keys:** Look for custom key definitions in `config/defines.h`. These macros can simplify complex keycodes or create aliases for common key combinations.
-   **Layer Definitions:** The `config/layers.h` file contains macros that define the structure of different layers, making the `.keymap` file a high-level overview of the keyboard layout.

When modifying the keymap, please adhere to these conventions:
1.  If you are adding a new complex key behavior or a frequently used key combination, add a macro for it in `config/defines.h`.
2.  Use the existing layer macros from `config/layers.h` to maintain the keymap's structure.
3.  Always check these files first to understand the existing helpers before adding new keys.

{
  description = "Development environment for 64-bit OS development";

  inputs = {
    # The only version with working i686 cross-compiler
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-24.11";
    flake-utils.url = "github:numtide/flake-utils";
  };

  outputs = { self, nixpkgs, flake-utils }:
    flake-utils.lib.eachDefaultSystem (system:
      let
        pkgs = nixpkgs.legacyPackages.${system};
      in
      {
        devShells.default = pkgs.mkShell {
          nativeBuildInputs = with pkgs; [
            # Cross-compiler for x86 bare metal
            pkgsCross.i686-embedded.buildPackages.binutils
	    pkgsCross.i686-embedded.buildPackages.gcc
	    # ARM64
	    pkgsCross.aarch64-embedded.buildPackages.binutils
	    pkgsCross.aarch64-embedded.buildPackages.gcc
	    # ARM
	    pkgsCross.arm-embedded.buildPackages.binutils
	    pkgsCross.arm-embedded.buildPackages.gcc



	    # Dev tools
	    clang-tools
	    bear  # Tool that generates a compilation database for clang tooling
	    gdb

	    # Additional useful tools for OS development
	    nasm        # Assembler for x86/x86_64
	    qemu        # For testing your OS
	    gvfs # 
	    # gdb         # Debugger
	    # hexdump     # For examining binary files
	    grub2       # Bootloader
	    libisoburn # required by grub
	    # xorriso     # For creating ISO images
	    # mtools      # For working with FAT filesystems
	  ];

          shellHook = ''
            echo "64-bit OS Development Environment"
            echo "================================="
            echo "Cross-compiler: x86_64-elf-gcc"
            echo "Available tools: nasm, qemu, grub" 
            echo ""
            echo "To verify cross-compiler:"
            echo "  x86_64-elf-gcc --version"
            echo ""
            echo "Example compile command:"
            echo "  x86_64-elf-gcc -c kernel.c -o kernel.o"
            echo ""
            echo "Happy OS hacking! 🚀"
	    zsh
          '';
        };
      });
}

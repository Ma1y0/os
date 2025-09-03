{
  description = "Development environment for 64-bit OS development";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";
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
	    # X86_64 cross-compiler
            pkgsCross.x86_64-embedded.buildPackages.binutils
	    pkgsCross.x86_64-embedded.buildPackages.gcc

	    # Dev tools
	    clang-tools
	    clang
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
	    xorriso     # For creating ISO images
	    # mtools      # For working with FAT filesystems
	  ];

          shellHook = ''
            echo "Happy OS hacking! 🚀"
	    zsh
          '';
        };
      });
}

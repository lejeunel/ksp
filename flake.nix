{
  description = "A Nix-flake-based Golang development environment";

  inputs.nixpkgs.url = "https://flakehub.com/f/NixOS/nixpkgs/0.1.*.tar.gz";

  outputs =
    { self, nixpkgs }:
    let
      supportedSystems = [
        "x86_64-linux"
        "aarch64-linux"
        "x86_64-darwin"
        "aarch64-darwin"
      ];
      forEachSupportedSystem =
        f: nixpkgs.lib.genAttrs supportedSystems (system: f { pkgs = import nixpkgs { inherit system; }; });
    in
    {
      devShells = forEachSupportedSystem (
        { pkgs }:
        {
          default = pkgs.mkShell {

            packages = with pkgs; [
              ccls
              gnumake
              cmake
              gcc
              catch2_3
            ];
          };
        }
      );
      packages = forEachSupportedSystem (
        { pkgs }:
        {
          default = pkgs.stdenv.mkDerivation {
            pname = "ksp";
            version = "0.1.0";
            src = ./.;
            nativeBuildInputs = with pkgs; [
              gnumake
              cmake
              gcc
              catch2_3
            ];
            # Enable running tests during build
            doCheck = true;

            enableParallelBuilding = true;
          };
        }
      );
    };
}

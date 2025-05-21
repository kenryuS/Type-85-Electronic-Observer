{
  description = "Nix flake for Type 85 Electronic Observer";

  inputs = {
    #nixpkgs.url = "github:NixOS/nixpkgs/nixos-24.11";
    nixpkgs.url = "nixpkgs";
    flake-utils.url = "github:numtide/flake-utils";
  };

  outputs = { self, nixpkgs, flake-utils, ... }:
    flake-utils.lib.eachDefaultSystem (system:
      let
        pkgs = nixpkgs.legacyPackages.${system};
        pname = "Type-85-Electronic-Observer";
        version = "0.0.1";
        src = ./.;
        buildInputs = with pkgs; [
        ];
        qtInputs = with pkgs.kdePackages; [
          qtwebengine
          qthttpserver
          qttranslations
          qtbase
          qttools
        ];
        nativeBuildInputs = with pkgs; [
          cmake
          pkg-config
          gdb
          doxygen
        ];
        PrintDepsFuncBody = l: builtins.toString (builtins.map (p: ''echo "${p}";'') l);
      in
      {
        devShells.default = pkgs.mkShell {
          inherit nativeBuildInputs;
          buildInputs = buildInputs ++ qtInputs;

          shellHook = ''
            export PS1="(devShell ${pname}) \w \$ "

            function PrintDeps () {
                ${PrintDepsFuncBody qtInputs}
            }
          '';
        };

        packages.default = pkgs.qt6Packages.callPackage pkgs.stdenv.mkDerivation {
          inherit pname version src;
          buildInputs = buildInputs ++ qtInputs;
          nativeBuildInputs = nativeBuildInputs ++ [ pkgs.kdePackages.wrapQtAppsHook ];
        };
      }
    );
}

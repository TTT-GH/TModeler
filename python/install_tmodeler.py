import sys
import os
import subprocess

def main():
    if len(sys.argv) != 2:
        print("❌ Usage : python install_tmodeler.py <version>")
        print("Exemple : python install_tmodeler.py 1.0.5")
        return

    version = sys.argv[1]
    wheel_name = f"tmodeler-{version}-py3-none-any.whl"
    wheel_path = os.path.join("dist", wheel_name)

    if not os.path.exists(wheel_path):
        print(f"❌ Le fichier '{wheel_path}' n'existe pas.")
        return

    print(f"🚀 Installation de {wheel_name} ...")
    result = subprocess.run(["pip", "install", wheel_path])

    if result.returncode == 0:
        print("✅ Installation réussie.")
    else:
        print("❌ Échec de l'installation.")

if __name__ == "__main__":
    main()
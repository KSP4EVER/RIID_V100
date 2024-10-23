import subprocess
import sys

def install(package):
    #"""Install a package using pip."""
    subprocess.check_call([sys.executable, "-m", "pip", "install", package, "--quiet","--no-warn-script-location"])

def check_and_install_modules(modules):
    #"""Check and install missing modules."""
    for module in modules:
        try:
            __import__(module)  # Try to import the module
            print(f"Module '{module}' is already installed.")
        except ImportError:
            print(f"Module '{module}' is not installed. Installing...")
            install(module)
            print(f"Module '{module}' installed")

if __name__ == "__main__":
    # List of required modules
    print("Checking for all required modules...")
    required_modules = ['matplotlib','serial']  
    check_and_install_modules(required_modules)

    print("All required modules are checked and installed.")
    sys.exit(1)


import sys, shutil, os

if len(sys.argv) > 1:
    shutil.copytree(os.getcwd(), sys.argv[1], dirs_exist_ok=True)

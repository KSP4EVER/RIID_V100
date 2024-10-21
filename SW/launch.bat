@echo off
python3 setup.py

if %ERRORLEVEL%==1 (
    python3 RadSpectra.py
) else (
    echo "An error occured in setup..."
)
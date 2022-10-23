#!/bin/python
"""
TLS Handshake Experiments
"""

import time
import os
import sys
import subprocess


ret = subprocess.run(["openssl", "s_client", "-connect", "gmail.com:443", ">","gmail1_com.txt"])
print(ret.stdout)

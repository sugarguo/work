#!/usr/bin/env python
# -*- coding: utf-8 -*-
import sys
sys.path.insert(0,'ext_lib')
import bottle, os, json
from project import app
from bottle import debug, run

debug(True)
if __name__ == '__main__':
    run(app,host='0.0.0.0',port=2002)

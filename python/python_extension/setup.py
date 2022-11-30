from setuptools import setup, Extension

module1 = Extension('mypymod',
                    sources = ['mypymod.c'])

setup (name = 'mypymod',
       version = '1.0',
       description = 'This is a demo package',
       ext_modules = [module1]
                                    )

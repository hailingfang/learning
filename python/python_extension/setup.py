from setuptools import setup, Extension

module1 = Extension('fhladd',
                    sources = ['fhladd.c'])

setup (name = 'fhladd',
       version = '1.0',
       description = 'This is a demo package',
       ext_modules = [module1]
                                    )

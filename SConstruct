import os

EnsurePythonVersion (2,2)

env = Environment ()

opts = Options()

if env['PLATFORM'] == 'win32':
   opts.AddOptions (PathOption('prefix',
                              'Installation prefix',
                              'C:\\\\Syx', []))
   env['bindir'] = env['datadir'] = env['libdir'] = '$prefix'
   env['imagepath'] = '$prefix\default.sim'
   env['includedir'] = '$prefix\include'
else:
   opts.AddOptions (
      PathOption('prefix', 
                 'Installation prefix', 
                 '/usr/local', []),
      PathOption('exec_prefix',
                 'Installation prefix for executables and object code libraries',
                 '$prefix', []),
      PathOption('bindir', 
                 'Installation prefix for user executables', 
                 '$exec_prefix/bin', []),
      PathOption('datadir',
                 'Installation prefix for packages',
                 '$prefix/share/syx', []),
      PathOption('imagepath',
                 'Installation path for the default binary image',
                 '$datadir/default.sim', []),
      PathOption('libdir',
                 'Installation prefix for object code libraries', 
                 '$exec_prefix/lib', []),
      PathOption('includedir',
                 'Installation prefix for C header files', 
                 '$prefix/include', []))

opts.AddOptions (
   BoolOption ('plugins', """Build with plugins support""", True),
   BoolOption ('attach', """Attach a debugger for test failures""", False),              
   EnumOption ('debug', """Debug output and symbols""", 'normal',
               allowed_values=('no', 'normal', 'info', 'full'),
               ignorecase=True),

   BoolOption ('GTK', """Build the syx-gtk plugin""", True),
   BoolOption ('READLINE', """Build the syx-readline plugin""", True))

opts.Update (env)

# My 64bit LFS keep its toolchain in /tools64 and set LD_LIBRARY_PATH for tests
if env['PLATFORM'] == 'posix':
   env['ENV']['PATH'] = '/tools64/bin:' + env['ENV']['PATH']

# Specify the alternative toolchain for Windows
env['tools'] = ['default', 'mingw']
   
# Custimize the help message
env.Help (opts.GenerateHelpText (env) + """
     Type: 'scons'               to build Syx.
           'scons plugins=no'    build without plugins support
           'scons debug=no'      release build with high optimization.
           'scons debug=normal'  add debug symbols (default).
           'scons debug=info' 	 display more messages.
           'scons debug=full'    trace the entire execution stack of Smalltalk.
           'scons test'          to test Syx.
           'scons test attach=yes'
                                 to test Syx and attach a debugger if the
                                 test failures
           'scons doc'           to create reference documentation (requires Doxygen).
           'scons install'       to install Syx.
     """)

# Configuration
conf = Configure (env, config_h='config.h')

print 'Mandatory headers...'

for h in ['string.h', 'unistd.h', 'sys/stat.h', 'time.h', 'stdio.h', 'assert.h', 'fcntl.h',
          'sys/types.h', 'errno.h', 'getopt.h']:
   if not conf.CheckCHeader (h):
      print "Can't build Syx without %s header!" % h
      env.Exit (1)

print
print 'Optional headers...'

for h in ['stdarg.h']:
   conf.CheckCHeader (h)
   
if env['PLATFORM'] == 'win32':
   have_windows_h = conf.CheckCHeader ('windows.h')

print
print 'Mandatory functions...'

for f in ['strtol', 'strtof', 'strtod', 'gettimeofday', 'getopt']:
   if not conf.CheckFunc (f):
      print "Can't build Syx without %s function!" % f
      env.Exit (1)

if env['PLATFORM'] == 'win32':
   if not conf.CheckLibWithHeader ('wsock32', 'winsock2.h', 'c', 'select(0, NULL, NULL, NULL, NULL);'):
      print "Can't build Syx without select function!"
      env.Exit (1)
else:
   if not conf.CheckFunc ('select'):
      print "Can't build Syx without select function!"
      env.Exit (1)

print
print 'Optional functions...'

for f in ['strndup']:
   conf.CheckFunc (f)

print
if env['plugins']:
    if (env['PLATFORM'] == 'win32' and have_windows_h) or conf.CheckLibWithHeader ('dl', 'dlfcn.h', 'c', 'dlopen(0, 0);'):
        env.MergeFlags ('-DWITH_PLUGINS')
    else:
        print 'WARNING: building without plugins support'
        env['plugins'] = False

conf.Finish ()

# Flags
env.MergeFlags ('-Wall -DHAVE_CONFIG_H -I#. -DROOT_PATH="$datadir" -DIMAGE_PATH="$imagepath"')
if env['debug'] == 'no':
   env.MergeFlags ('-O3')
elif env['debug'] == 'normal':
   env.MergeFlags ('-g -O2')
elif env['debug'] == 'info':
   env.MergeFlags ('-g -O -DSYX_DEBUG_INFO')
elif env['debug'] == 'full':
   env.MergeFlags ('-g -O -DSYX_DEBUG_INFO -DSYX_DEBUG_FULL')

if env['PLATFORM'] == 'win32':
   env.MergeFlags ('-DWINDOWS')

# Test builder
def builder_test (target, source, env):
   print
   app = str (source[0].path)
   relapp = os.path.splitext (os.path.basename (str (source[0].abspath)))[0]
   f = open(target[0].abspath, 'w')
   if env.Execute (app) == 0:
      print 'PASS: %s' % relapp
      f.write ('PASSED')
   else:
      print 'FAIL: %s' % relapp
      f.write ('FAILED')
      if env['attach']:
          app = 'gdb '+app
          env.Execute (app)
   f.close ()

action = env.Action (builder_test, lambda *args, **kwargs: '')
builder = env.Builder (action=action)
env.Append(BUILDERS = { 'Test' : builder })

# Doc builder

env.Alias ('doc', env.Command ('build/docs', 'Doxyfile',
                               'doxygen $SOURCES'))
env.Clean ('doc', 'build/doc')

# Build

env.MergeFlags ('-L#build/lib')
env.BuildDir ('build/lib', 'syx', False)
env.SConscript (dirs=['build/lib'], exports=['env'])

env.BuildDir ('build/bin', 'src', False)
env.SConscript (dirs=['build/bin'], exports=['env'])

env.BuildDir ('build/plugins', 'plugins', False)
env.SConscript (dirs=['build/plugins'], exports=['env'])

env.SConscript (dirs=['tests'], exports=['env'])

# Install data

target = env.Install (env['datadir'], '#st')
env.Clean (target, os.path.join(env['datadir'], 'st'))
env.Alias ('install', env['datadir'])
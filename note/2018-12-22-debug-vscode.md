生成 Makefile 时添加 `-g` 选项来 enable debug

注意 debug 的时候优化设置为 `-O0`

```
cd concorde && CFLAGS='-O0 -march=native -mtune=native -fPIC -g' ./configure
cd LINKERN && make -j && mv linkern ../../
```

然后在 VSCode 里配置下面两个文件：

### launch.json

```
{
    "version": "0.2.0",
    "configurations": [
        {
            "name": "(gdb) Launch",
            "type": "cppdbg",
            "request": "launch",
            "program": "${workspaceRoot}\\LINKERN\\linkern.exe",
            "cwd": "${workspaceRoot}\\LINKERN",
            "args": ["-s", "42", "-S", "linkern.tour", "-R", "1000000000", "-t", "30", "cities1k.tsp"],
            "stopAtEntry": false,
            "environment": [],
            "externalConsole": true,
            "MIMode": "gdb",
            "miDebuggerPath": "C:\\MinGW\\bin\\gdb.exe",
            //"preLaunchTask": "build",
            "setupCommands": [
                {
                    "description": "Enable pretty-printing for gdb",
                    "text": "-enable-pretty-printing",
                    "ignoreFailures": true
                }
            ]
        }
    ]
}
```

### tasks.json

```
{
    "version": "2.0.0",
    "tasks": [
        {
            "label": "build",
            "type": "shell",
            "command": "make",
            // use options.cwd property if the Makefile is not in the project root ${workspaceRoot} dir
            "options": {
                "cwd": "${workspaceRoot}\\LINKERN"
            },
            // start the build without prompting for task selection, use "group": "build" otherwise
            "group": {
                "kind": "build",
                "isDefault": true
            },
            "presentation": {
                "echo": true,
                "reveal": "always",
                "focus": false,
                "panel": "shared"
            },
            // arg passing example: in this case is executed make QUIET=0
            "args": ["QUIET=0"],
            // Use the standard less compilation problem matcher.
            "problemMatcher": {
                "owner": "cpp",
                "fileLocation": ["absolute"],
                "pattern": {
                    "regexp": "^(.*):(\\d+):(\\d+):\\s+(warning|error):\\s+(.*)$",
                    "file": 1,
                    "line": 2,
                    "column": 3,
                    "severity": 4,
                    "message": 5
                }
            }
        }
    ]
}
```

替换默认 Terminal 从 PowerShell 到 Git Bash:

https://code.visualstudio.com/docs/editor/integrated-terminal
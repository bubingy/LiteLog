# Introduction 
A thread-safe and light weight log system.

# Getting Started
There are 2 log classes: ConsoleLogger & FileLogger, which output log message to console or file with format:
```
[DataTime] - <Title> - <Level> - <Message>
```

Here is an example:
```
[2020-07-28 13:08:15] - litelog - DEBUG - This is an example!
```

## Usage of ConsoleLogger
For example:
```
ConsoleLogger logger;
logger(level, title)<<message<<endl;
```
where `level` is the short for `log level` and `title` usually can be set as the name of the application.

Replace `level` with one of the following value:
* `Level::Debug`
* `Level::Info`
* `Level::Warn`
* `Level::Error`
* `Level::Fatal`

## Usage of FileLogger
It's similar to ConsoleLogger. The only difference is constructor:
```
FileLogger logger("log.txt");
```

# trader

Setup:
Windows
- In build\shell.cmd, build poco with deploy_poco.cmd
- Run build\genproj.cmd
- Copy bin\*.json & bin\*.properties to bin\debug on bin\release and modify the config with api keys and proxy settings

Todo:

High Priority
1. Cryptowatch
	- Implement all other cryptowatch api endpoints
	- Automatic allowance recording to database
	- Modify invoke to introspect allowance and remove allowance from hyperschema for endpoints

2. Kraken
	- Prototype Websockets
	- Implement kraken api
	- Implement kraken database
	
3. Compile on Linux
	- Compile on WSL
	
4. Integrate CI on Appveyor

5. Integrate CI on Travis

6. Integrate with task management/chat tools, i.e. Slack

7. Investigate sqlitefs master/slave replication

8. Investigate Mathlab integration for visualization (ODBC/JDBC)

9. Investigate Excel integration for visualization (ODBC)

10. Deploy on Google App/EC2

Medium Priority
1. Integrate valijson to validate hyperschema, databaseschema and configschema
2. Windows run as a service


Low Priority
1. More versatile #ref implementation in objectschemadefinition, must be able to nest multiple #refs

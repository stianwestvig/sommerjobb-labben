# sommerjobb-labben
Sommerjobb 2018 for Bouvet Labben

## Legge til nytt repo
Bare lag alle eksperimenter i nye mapper under her

## Vår plan den første uken

1. Koble sammen en arduino med sensorer og data via mobilt nettverk
2. Innstallere amazon-iot c++ sdk på arduinoene
3. Distribuere amazon-iot device sertifikater (ett til hver arduino)
4. Sende data fra hver arduino til amazon-iot.
   Forslag til MQTT message topic /messages/devices/[deviceId]
   Da kan vi enklet tappe data fra alle devicer eller fra en og en
5. Sette opp regler i amazon-iot rules engine for å styre data til S3 lagring


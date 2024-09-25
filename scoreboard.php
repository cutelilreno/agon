<?php
use agon\Scoreboard;
use agon\remoteWebdavFile;
include "includes/agon.inc";
const WEBDAVINI = "webdav.ini";

$objective = "FunStat";
$uv_scoreboard_file = new remoteWebdavFile(parse_ini_file(WEBDAVINI));
echo $uv_scoreboard_file->getLastModified() . "\n";
$scoreboard = new Scoreboard($uv_scoreboard_file->getGzDecodeFile());
foreach ($scoreboard->getObjectiveList($objective) as $key => $value) {
    echo $key . ": " . $value . "\n";
}
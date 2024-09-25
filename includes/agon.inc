<?php
namespace agon;

use Nbt\DataHandler;
use Nbt\Service;
use Sabre\DAV\Client;
include 'vendor/autoload.php';
class scoreboard {
    public $scoreboard_list;
    private $tree;
    public function __construct(string $nbt_string) {
        $nbt_service = new Service(new DataHandler());
        $this->tree = $nbt_service->readString($nbt_string);
        $this->scoreboard_list = $this->tree->findChildByName('PlayerScores');
    }
    public function getObjectiveList(string $objective): array
    {
        $objective_list = [];
        foreach ($this->scoreboard_list->getChildren() as $player) {
            if ($player->findChildByName("Objective")->getValue() == $objective) {
                $name = $player->findChildByName("Name")->getValue();
                $score = $player->findChildByName("Score")->getValue();
                $objective_list += array($name => $score);
            }
        }
        arsort($objective_list);
        return $objective_list;
    }
}

class remoteWebdavFile {
    protected Client $client;
    public function __construct(array $webdav_settings) {
        $this->client = new Client($webdav_settings);
    }

    public function getLastModified(): int
    {
        $response = $this->client->request('HEAD');
        return strtotime($response['headers']['last-modified'][0]);
    }
    public function getGzDecodeFile(): string
    {
        $response = $this->client->request('GET');
        $body = $response['body'];
        return gzdecode($body);
    }
}
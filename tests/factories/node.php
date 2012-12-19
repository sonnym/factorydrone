<?php
PhactoryDrone::define('node', 'node', array(
  'type' => PhactoryDrone::create('content type')->type,
  'title' => PhactoryDrone::sequence(function ($n) { return "node_title{$n}"; }),
  'status' => 1,
));

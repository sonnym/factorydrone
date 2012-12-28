<?php
FactoryDrone::define('node', 'node', array(
  'type' => FactoryDrone::create('content type')->type,
  'title' => FactoryDrone::sequence(function ($n) { return "node_title{$n}"; }),
  'status' => 1,
));

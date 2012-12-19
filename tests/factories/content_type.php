<?php
PhactoryDrone::define('content type', 'content type', array(
  'type' => PhactoryDrone::sequence(function ($n) { return "page${n}"; }),
  'name' => PhactoryDrone::sequence(function ($n) { return "Page Type ${n}"; }),
  'base' => 'node_content',
  'description' => 'A simple page',
));

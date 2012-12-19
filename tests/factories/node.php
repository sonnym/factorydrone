<?php
Factory::define('node', 'node', array(
  'type' => Factory::create('content type')->type,
  'title' => Factory::sequence(function ($n) { return "node_title{$n}"; }),
  'status' => 1,
));

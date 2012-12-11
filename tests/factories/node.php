<?php
Factory::define('node', 'node', array(
  'type' => ContentTypeFactory::create('content type')->type,
  'title' => Factory::sequence(function ($n) { return "node_title{$n}"; }),
  'status' => 1,
));

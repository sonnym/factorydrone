<?php
Factory::define('content_type', 'content type', array(
  'type' => Factory::sequence(function ($n) { return "page${n}"; }),
  'name' => Factory::sequence(function ($n) { return "Page Type ${n}"; }),
  'base' => 'node_content',
  'description' => 'A simple page',
));

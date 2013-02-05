<?php
FactoryDrone::define('menu link', 'menu link', array(
  'link_path' => '/',
  'link_title' => FactoryDrone::sequence(function ($n) { return "link_title${n}"; }),
));

<?php
class PhactoryDroneTestCase extends DrupalWebTestCase {
  public function setUp($modules = array()) {
    parent::setUp($modules);
  }

  protected function load_factory_definitions() {
    Factory::add_factory_path(join(DIRECTORY_SEPARATOR, array(dirname(__FILE__), 'factories')));
    Factory::load_definitions();
  }
}

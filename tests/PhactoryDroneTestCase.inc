<?php
class PhactoryDroneTestCase extends DrupalWebTestCase {
  public function setUp($modules = array()) {
    parent::setUp($modules);
  }

  protected function load_factory_definitions() {
    PhactoryDrone::add_factory_path(join(DIRECTORY_SEPARATOR, array(dirname(__FILE__), 'factories')));
    PhactoryDrone::load_definitions();
  }

  protected function assertThrows($message, $cb) {
    try {
      $cb();
    } catch (Exception $e) {
      $this->assertEqual($e->getMessage(), $message);
    }
  }
}

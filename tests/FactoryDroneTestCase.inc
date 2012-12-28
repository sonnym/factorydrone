<?php
class FactoryDroneTestCase extends DrupalWebTestCase {
  public function setUp($modules = array()) {
    parent::setUp($modules);
  }

  protected function load_factory_definitions() {
    FactoryDrone::add_factory_path($this->factory_path);
    FactoryDrone::load_definitions();
  }

  protected function assertThrows($message, $cb) {
    try {
      $cb();
    } catch (Exception $e) {
      $this->assertEqual($e->getMessage(), $message);
    }
  }

  public function __get($name) {
    if ($name == 'factory_path') {
      return join(DIRECTORY_SEPARATOR, array(dirname(__FILE__), 'factories'));
    }
  }
}

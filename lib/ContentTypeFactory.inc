<?php
/**
 * @file
 * Contains ContentTypeFactory.
 */

class ContentTypeFactory {
  /**
   * A method for creating content types
   *
   * The conent type is created with the supplied options, persisted, and
   * returned to the caller.
   *
   * @param string $name
   *   The name of the factory to generate
   *
   * @param array $opts
   *   An associative array with options for the node
   *   - title: The title of the node.
   *   - status: The published status of the node.
   *
   * @return stdClass
   *   The new content type
   */
  public static function create($name, $opts = array()) {
    $content_type = (object) array_merge(Factory::get_default_options($name), $opts);

    node_type_save($content_type);

    return $content_type;
  }
}

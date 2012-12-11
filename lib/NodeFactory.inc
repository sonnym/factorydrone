<?php
/**
 * @file
 * Contains NodeFactory.
 */

class NodeFactory {
  /**
   * A method for creating content nodes
   *
   * The node is created with the supplied options, persisted, and
   * returned to the caller.
   *
   * @param string $name
   *   The name of the factory to generate
   *   - title: The title of the node.
   *   - status: The published status of the node.
   *
   * @param array $opts
   *   An associative array with options for the node
   *
   * @return stdClass
   *   The new node
   */
  public static function create($name, $opts = array()) {
    $node = (object) array_merge(Factory::get_default_options($name), $opts);

    node_save($node);

    return $node;
  }
}

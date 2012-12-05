<?php
/**
 * @file
 * Contains VocabularyFactory.
 */

class VocabularyFactory {
  /**
   * A method for creating taxonomy vocabularies
   *
   * The vocabulary is created with the supplied options, persisted, and
   * returned to the caller.
   *
   * @param array $opts
   *   An associative array with options for the vocabulary
   *   - name: The human-readable name of the vocabulary.
   *   - machine_name: The machine name of the vocabulary.
   *   - hierarchy: The hierarchy level of the vocabulary.
   *
   * @return stdClass
   *   The new vocabulary
   *
   * @see http://api.drupal.org/api/drupal/modules%21taxonomy%21taxonomy.module/function/taxonomy_vocabulary_save/7
   */
  public static function create($opts = array()) {
    $vocabulary = (object) $opts;

    taxonomy_vocabulary_save($vocabulary);

    return $vocabulary;
  }
}

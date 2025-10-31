<?php

function nel_preprocess_node__review_question(&$variables) {

  $node = $variables['node'];

  // Get systematic review cover image
  $variables['cover_image'] = null;
  if (
    $node->hasField('field_systematic_review')
    && $review_entity = $node->field_systematic_review->entity
  ) {
    $uri = $review_entity->get('field_cover_image')->entity->get('field_media_image')->entity->uri->value;
    $img = \Drupal::service('file_url_generator')->generateString($uri);

    $variables['cover_image'] = $img;

  }

}

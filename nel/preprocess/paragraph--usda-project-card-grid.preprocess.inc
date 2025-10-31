<?php
  /**
   * Implements hook_preprocess_paragraph__usda_project_card_grid().
   */
  function nel_preprocess_paragraph__usda_project_card_grid(&$variables) {
    $category_id = $variables['elements']['field_category']['#items']->getValue()[0]['target_id'];

    $nids = \Drupal::entityQuery('node')
        ->accessCheck(true)
        ->condition('status', 1)
        ->condition('type', ['project_page', 'systematic_review'],'IN')
        ->condition('field_project_category', $category_id, 'IN')
        ->sort('created', 'DESC')
        ->execute();

        $nodeStorage = \Drupal::entityTypeManager()->getStorage('node');
        $projects = $nodeStorage->loadMultiple($nids);

        foreach ($projects as $project) {
          $title = $project->title->value;
          $url = $project->toUrl('canonical', ['absolute' => false])->toString();

          // There should always be an image, but if there isn't one, we'll need to handle it
          // Maybe use a placeholder image?
          $img = null;

          $review_entity = $project->field_systematic_review->entity;
          $imgEntity = $review_entity?->get('field_cover_image')->entity;
          if ($imgEntity) {
            $uri = $imgEntity->get('field_media_image')->entity->uri->value;
            if ($uri) {
              $img = \Drupal::service('file_url_generator')->generateString($uri);
            }
          }

          $variables['items'][] = [
            'title' => $title,
            'url' => $url,
            'cover_image' => $img
          ];

        }
  }

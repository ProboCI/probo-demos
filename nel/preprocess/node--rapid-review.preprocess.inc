<?php

use Drupal\Core\Url;
function nel_preprocess_node__rapid_review(&$variables) {

    $node = $variables['node'];

    $request = \Drupal::request();
    $route_match = \Drupal::routeMatch();
    $title = \Drupal::service('title_resolver')->getTitle($request, $route_match->getRouteObject());

    $variables['title'] = $title;

    // Current Systematic Review
    $systematic_review_page = $node->field_systematic_review_page->entity;

        // Page
        $systematic_review_page_url = $systematic_review_page->toUrl()->toString();
        $systematic_review_page_title = $systematic_review_page->getTitle();

        // PDF
        $entity = $node->field_file->entity;
        $uri = $entity->get('field_media_file')->entity->uri->value;
        $systematic_review_pdf_url = \Drupal::service('file_url_generator')->generateString($uri);

        $force_download = $node->field_force_download->value;

        $variables['current_systematic_review'] = [
            'url' => $systematic_review_page_url,
            'title' => $systematic_review_page_title,
            'pdf' => $systematic_review_pdf_url,
            'force_download' => $force_download ? 'true' : 'false',
        ];


    $variables['main_content_array'] = [];
    if (!empty($variables['elements']['field_main_content'])) {
        foreach ($variables['elements']['field_main_content'] as $delta => $item) {
            if (is_array($item) && isset($item['#paragraph'])) {
                $paragraph = $item['#paragraph'];
                $paragraph_type = $paragraph->type->entity->label();

                $title = getFieldValue($paragraph, 'field_title');
                $body = getFieldValue($paragraph, 'field_body');
                $id_override = getFieldValue($paragraph, 'field_id');
                $button_label = getFieldValue($paragraph, 'field_label');

                $id = ($id_override != "") ? $id_override : $title;

                // Get the image if it exists
                $cover_image_override_field = $paragraph->field_cover_image_override;
                $cover_image_taxonomy = $paragraph->field_systematic_review;
                if (
                    $cover_image_override_field &&
                    $cover_image_override_field->entity
                ) {
                    $cover_image_uri = $cover_image_override_field->entity->get('field_media_image')->entity->uri->value;
                } elseif (
                    $cover_image_taxonomy &&
                    $cover_image_taxonomy->entity
                ) {
                    $cover_image_uri = $cover_image_taxonomy->entity->get('field_cover_image')->entity->get('field_media_image')->entity->uri->value;
                }

                $cover_image = (isset($cover_image_uri)) ? \Drupal::service('file_url_generator')->generateString($cover_image_uri) : null;

                $variables['main_content_array'][] = [
                    'type' => $paragraph_type,
                    'title' => $title,
                    'body' => $body,
                    'button_label' => $button_label,
                    'cover_image' => $cover_image,
                    'id' => slugify($id),
                ];

            }
        }

    }

    $variables['past_systematic_reivews_array'] = [];
    if (isset($variables['node']->field_internal_links)) {

        $entries = $variables['node']->field_internal_links;

        foreach ($entries as $entry) {
            if ($entry->entity) {
                $entity = $entry->entity;
                $url = Url::fromRoute('entity.node.canonical', ['node' => $entity->id()])->toString();
                $title = $entity->label();
                $past_systematic_reivews_array[] = [
                'url' => $url,
                'title' => $title,
                ];
            }
        }
        $variables['past_systematic_reivews_array'] = $past_systematic_reivews_array;
    }


    $variables['additional_resources_array'] = [];
    if (!empty($variables['elements']['field_additional_resources'])) {
        foreach ($variables['elements']['field_additional_resources'] as $delta => $item) {
            if (is_array($item) && isset($item['#paragraph'])) {
                $paragraph = $item['#paragraph'];

                $title = $paragraph->get('field_title')->value;

                $selected_button_value = $paragraph->get('field_button_label')->value;
                $allowed_values = \Drupal::service('entity_field.manager')
                  ->getFieldStorageDefinitions('paragraph')['field_button_label']
                  ->getSettings()['allowed_values'];
                $button_label = $allowed_values[$selected_button_value] ?? $selected_button_value;
                $aria_label_array = [
                    'download' => 'Download ' . $title,
                    'view_now' => 'View ' . $title,
                    'learn_more' => 'Learn more about ' . $title,
                ];

                $entity = $paragraph->field_media->entity;
                $uri = $entity->get('field_media_file')->entity->uri->value;
                $url = \Drupal::service('file_url_generator')->generateString($uri);

                $variables['additional_resources_array'][] = [
                    'title' => $title,
                    'url' => $url,
                    'button_label' => $button_label,
                    'aria_label' => $aria_label_array[$selected_button_value] ?? $title,
                ];
            }
        }
    }
}

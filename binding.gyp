{
  'targets': [
    {
      'target_name': 'fann2',
      'include_dirs': [ "<!(node -e \"require('nan')\")" ],
      'link_settings': {
        # linking against -ldoublefann against of -lfann
        'libraries': [
          '-ldoublefann',
        ],
      },
      'sources': [
        'src/fann-accs.cc',
        'src/fann-arrs.cc',
        'src/fann-cascade.cc',
        'src/fann-create.cc',
        'src/fann-train.cc',
        'src/fann-util.cc',
        'src/fann.cc'
      ],
      'conditions': [
        [ 'OS=="win"', {
            'library_dirs': [
                '<(nodedir)\Release'
            ]
        },
		{
          'include_dirs': [
            '/opt/local/include'
          ],
          'library_dirs': [
            '/opt/local/lib'
          ]
        }],
      ],
    }
  ]
}

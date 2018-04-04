{
  "targets": [
    {
      "target_name": "noppai",
      "sources": [ "src/noppai.cc" ],
      "include_dirs": [
        "src/oppai-ng/",
        "<!(node -e \"require('nan')\")"
      ]
    }
  ]
}
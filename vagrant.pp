exec { "update":
  path => "/usr/bin",
  command => "apt-get update",
}

package { "gdb":
  ensure  => present,
  require => Exec["update"],
}

package { "nasm":
  ensure  => present,
  require => Exec["update"],
}

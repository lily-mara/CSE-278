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

package { "make":
  ensure  => present,
  require => Exec["update"],
}

package { "gcc":
  ensure  => present,
  require => Exec["update"],
}
